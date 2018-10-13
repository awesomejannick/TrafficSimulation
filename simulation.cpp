#include "traffic.h"

Traffic::Traffic(QWidget *parent) : QOpenGLWidget(parent) {
    road = QVector<QVector<Site>> (100, QVector<Site> (2));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

Traffic::~Traffic() {
    Q_UNIMPLEMENTED();
}

void Traffic::updateTraffic() {
    //TODO: second lane
    //TODO: better variable names
    int n = road.size();
    QVector<QVector<Site>> road2 = road;
    float pn = averageDensity();
    for (int i = 0; i < n; i++) {
        // formula 1
        float dp = road[i][0].getDensity() * road[i][0].getVelocity() -
        road[(i-1+n)%n][0].getDensity() * road[(i-1+n)%n][0].getVelocity();
        road2[i][0].setDensity(road[i][0].getDensity() - dp);
        // formula 2
        float nv = (pn * road[(i+1)%n][0].optimalVelocity(pn, pc)) / dp;
        road2[i][0].setVelocity(nv);
    }
    road = road2;
}

float Traffic::averageDensity() {
    double total = 0;
    for (int i = 0; i < road.size(); i++) {
        total += road[i][0].getDensity() + road[i][1].getDensity();
    }
    return total / (road.size()*2);
}
