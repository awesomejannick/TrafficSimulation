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
#define rlength 101

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
    void on_modeButton0_toggled(bool checked);
    void on_modeButton1_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    void updateLane(int lane);
    void plotLane(int lane);
    float averageDensity();
    void setMode(int mode);

    QOpenGLShaderProgram *shaderProg;
    GLuint VAO, coordVBO, colorVBO;

    QVector<QVector<Site>> road;

    static constexpr float pc = 0.175; //TODO: tweak variable
    static constexpr float g = 0.2;

    int mode;
    int NLANES = 2;

    static constexpr float tau = 0.5; //relaxation time in min
    static const int th0 = 45;        //initial velocity variance in (km/h)^2
    static const int k0 = 600;        //flux of velocity variance in km/h
    static constexpr float dt = 0.75; //reaction time in s
    static const int v0 = 120;        //initial speed in km/h
    static const int eta0 = 600;      //viscosity coefficient in km/h
    static constexpr float l = 0.005;     //vehicle length in km
    static constexpr float rhomax = 1 / l;
};

#endif // MAINWINDOW_H
