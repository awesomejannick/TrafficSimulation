#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include "mainwindow.h"

class Traffic : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core {
    Q_OBJECT

public:
    Traffic(QWidget *parent = 0);
    ~Traffic();

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    static float tau = 0.5;     //relaxation time
    static int th0 = 45;        //initial velocity variance
    static int k0 = 600;        //flux of velocity variance
    static int dt = 750;        //timestep
    static int v0 = 120;        //initial speed
    static int eta0 = 600;      //viscosity coefficient
    static int l = 5;           //car length
};

#endif // TRAFFIC_H
