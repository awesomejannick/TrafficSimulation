#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->setPen(QPen(Qt::blue));

    ui->widget->xAxis->setRange(0, rlength - 1);

    ui->widget2->addGraph();
    ui->widget2->addGraph();
    ui->widget2->graph(0)->setPen(QPen(Qt::red));
    ui->widget2->graph(1)->setPen(QPen(Qt::blue));

    ui->widget2->xAxis->setRange(0, rlength - 1);

    setMode(1);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTraffic()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTraffic() {
    updateLane(0);
    if (mode == 1) {
        updateLane(1);
    }

    for(int i = 0; i < NLANES; i++) {
        updateLane(i);
        plotLane(i);
    }
}

void MainWindow::updateLane(int lane) {
    //TODO: better variable names
    int n = road.size();
    QVector<QVector<Site>> road2 = road;

    if (mode == 1) {
        float pn = averageDensity();
        float w = abs(pn * pn * -1 / (pow(pn*cosh(1/pc - 1/pn),2)));
        float l1 = lane, l2 = (lane+1)%NLANES;

        for (int i = 0; i < n; i++) {
            // formula 1
            float dp = w*(road[(i+1)%n][l2].getDensity() - 2*road[i][l1].getDensity() + road[(i+n-1)%n][l2].getDensity())
               - pn*(road[i][l1].getDensity()*road[i][l1].getVelocity() - road[(i+n-1)%n][l1].getDensity()*road[(i+n-1)%n][l1].getVelocity());
            road2[i][lane].setDensity(road[i][lane].getDensity() + dp);
            // formula 2
            float nv = (pn * road[(i+1)%n][lane].optimalVelocity(pn, pc)) / road2[i][lane].getDensity();
            road2[i][lane].setVelocity(nv);
        }
        road = road2;
    } else {
        QVector<double> rho(n), v(n), th(n), p(n), ve(n), the(n), j(n);
        double d, i2, rs, eta, k, s, dr, dv, dp, dj, dth;

        for (int i = 0; i < n; i++) {
            rho[i] = road[i][0].getDensity();
            v[i] = road[i][0].getVelocity();
            th[i] = road[i][0].getVariance();
            d = -0.00000372 / (1+exp((rho[i]/rhomax - 0.25) / 0.06));
            ve[i] = v0 * d;
            the[i] = th0 * d;
        }
        for (int i = 0; i < n; i++) {
            i2 = (i+1)%n;
            dth = th[i2] - th[i];
            dv = v[i2] - v[i];
            s = l + v[i]*dt;
            rs = 1 - rho[i] * s;
            k = k0 / rs;
            eta = eta0 / rs;
            j[i] = -k*dth;
            p[i] = rho[i]*th[i] / (1 - rho[i]*s) - eta*dv;
        }
        for (int i = 0; i < n; i++) {
            i2 = (i+1)%n;
            //Calculate derivatives:
            dr = rho[i2] - rho[i];
            dv = v[i2] - v[i];
            dp = p[i2] - p[i];
            dj = j[i2] - j[i];
            dth = th[i2] - th[i];

            if (rho[i] - dr * dv < 0) {
                d = -0.00000372 / (1+exp((rho[i]/rhomax - 0.25) / 0.06));
                qDebug() << rho << v << th;
                qDebug() << i << d;
                qDebug() << rho[i] << v[i] << th[i];
                qDebug() << ve[i] << the[i] << j[i] << p[i];
                qDebug() << dr << dv << dp << dj << dth << endl << endl;
            }

            //Update road values:
            road[i][0].setDensity(
                rho[i] - dr * dv
            );
            road[i][0].setVelocity(
                v[i] - dp/rho[i] - v[i]*dv + (ve[i] - v[i])/tau
            );
            road[i][0].setVariance(
                th[i] - 2*p[i]*dv/rho[i] - dj/rho[i] + 2*(the[i] - th[i])/tau - v[i]*dth
            );
        }
    }
}

void MainWindow::plotLane(int lane) {
    QVector<double> densities(road.size());
    QVector<double> velocities(road.size());
    QVector<double> indices(road.size());
    for(int i = 0; i < road.size(); i++) {
        densities[i] = road[i][lane].getDensity();
        velocities[i] = road[i][lane].getVelocity();
        indices[i] = i;
    }
    ui->widget->graph(lane)->setData(indices, densities);
    ui->widget2->graph(lane)->setData(indices, velocities);
    ui->widget->replot();
    ui->widget2->replot();
}

float MainWindow::averageDensity() {
    double total = 0;
    for (int i = 0; i < road.size(); i++) {
        total += road[i][0].getDensity();
        total += road[i][1].getDensity();
    }
    return total / (road.size()*2);
}

void MainWindow::setMode(int mode) {
    this->mode = mode;

    if (mode==1) {
        NLANES = 2;
        road = QVector<QVector<Site>> (rlength, QVector<Site> (NLANES));
        for(int i = 0; i < 50; i++) {
            road[i][0] = Site(0.15, 1, th0);
            road[i][1] = Site(0.2, 1, th0);
        }
        for(int i = 50; i < rlength; i++) {
            road[i][0] = Site(0.2, 1, th0);
            road[i][1] = Site(0.15, 1, th0);
        }
        ui->widget->yAxis->setRange(0,1);
        ui->widget2->yAxis->setRange(0,10);
        ui->widget->graph(1)->setVisible(true);
        ui->widget2->graph(1)->setVisible(true);
    } else {
        NLANES = 1;
        road = QVector<QVector<Site>> (rlength, QVector<Site>(NLANES));
        for(int i = 0; i < 80; i++) {
            road[i][0] = Site(2, v0, th0);
        }
        for(int i = 80; i < rlength; i++) {
            road[i][0] = Site(3, v0, th0);
        }
        ui->widget->yAxis->setRange(-100, 100);
        ui->widget2->yAxis->setRange(-150, 150);
        ui->widget->graph(1)->setVisible(false);
        ui->widget2->graph(1)->setVisible(false);
    }
}
