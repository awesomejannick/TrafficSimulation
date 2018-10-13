#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    for(int i = 0; i < NLANES; i++) {
        ui->widget->addGraph();
        ui->widget->graph(i)->setPen(QPen(QColor(rand()%256, rand()%256, rand()%256)));
    }

    road = QVector<QVector<Site>> (100, QVector<Site> (2));
    for(int i = 0; i < 50; i++) {
        road[i][0] = Site(0.15);//((float)(rand() % 100)) / 200.0 + 0.5);
        road[i][1] = Site(0.2);
    }
    for(int i = 50; i < 100; i++) {
        road[i][0] = Site(0.2);//((float)(rand() % 100)) / 200.0 + 0.5);
        road[i][1] = Site(0.15);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTraffic()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTraffic() {
    updateLane(0);
    updateLane(1);

    for(int i = 0; i < NLANES; i++) {
        updateLane(i);
        plotLane(i);
    }

    ui->widget->xAxis->setRange(0,100);
    ui->widget->yAxis->setRange(-1,1);
    ui->widget->replot();
}

void MainWindow::updateLane(int lane) {
    //TODO: better variable names
    int n = road.size();
    QVector<QVector<Site>> road2 = road;
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
}

float MainWindow::averageDensity() {
    double total = 0;
    for (int i = 0; i < road.size(); i++) {
        total += road[i][0].getDensity();
        total += road[i][1].getDensity();
    }
    return total / (road.size()*2);
}
