#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>

#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QPen>
#include <QColor>

#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include "site.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateTraffic();

private:
    Ui::MainWindow *ui;

    void updateLane(int lane);
    void plotLane(int lane);
    float averageDensity(int lane);

    QOpenGLShaderProgram *shaderProg;
    GLuint VAO, coordVBO, colorVBO;

    QVector<QVector<Site>> road;

    static constexpr float pc = 0.175; //TODO: tweak variable
    static const int NLANES = 2;

    /*tatic constexpr float tau = 0.5; //relaxation time
    static const int th0 = 45;        //initial velocity variance
    static const int k0 = 600;        //flux of velocity variance
    static const int dt = 750;        //timestep
    static const int v0 = 120;        //initial speed
    static const int eta0 = 600;      //viscosity coefficient
    static const int l = 5;           //car length*/
};

#endif // MAINWINDOW_H
