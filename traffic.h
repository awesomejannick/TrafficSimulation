#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>

#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include "mainwindow.h"
#include "site.h"

class Traffic : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core {
    Q_OBJECT

public:
    Traffic(QWidget *parent = 0);
    ~Traffic();

    void updateTraffic();

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void createShaderPrograms();
    void createBuffers();
    void paintGL();
    void renderTraffic();

    float averageDensity();

    QOpenGLShaderProgram *shaderProg;
    GLuint VAO, coordVBO, colorVBO;

    QVector<QVector<Site>> road;

    static constexpr float pc = 0.1; //TODO: tweak variable


    /*tatic constexpr float tau = 0.5; //relaxation time
    static const int th0 = 45;        //initial velocity variance
    static const int k0 = 600;        //flux of velocity variance
    static const int dt = 750;        //timestep
    static const int v0 = 120;        //initial speed
    static const int eta0 = 600;      //viscosity coefficient
    static const int l = 5;           //car length*/
};

#endif // TRAFFIC_H
