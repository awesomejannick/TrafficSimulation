#include "traffic.h"

void Traffic::initializeGL() {
    initializeOpenGLFunctions();

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    createShaderPrograms();
    createBuffers();
}

// Loads all necessary shaders.
void Traffic::createShaderPrograms() {
    shaderProg = new QOpenGLShaderProgram();
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
    shaderProg->link();
}

// Creates the buffers in which data will be passed to the shaders.
void Traffic::createBuffers() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &coordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, coordVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindVertexArray(0);
}

void Traffic::paintGL() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind shader
    shaderProg->bind();
    glBindVertexArray(VAO);

    // Update data
    updateTraffic();

    // Render data
    renderTraffic();

    // Release shader
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    shaderProg->release();
}

void Traffic::resizeGL(int w, int h) {
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void Traffic::renderTraffic() {
    QVector<QVector2D> rendercoords(6);
    rendercoords.append(QVector2D(0,0.25));
    rendercoords.append(QVector2D(1,0.25));
    rendercoords.append(QVector2D(0,0.50));
    rendercoords.append(QVector2D(1,0.50));
    rendercoords.append(QVector2D(0,0.75));
    rendercoords.append(QVector2D(1,0.75));
    QVector<QVector3D> rendercolors(6,QVector3D(1,1,1));

    glBindBuffer(GL_ARRAY_BUFFER, coordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * rendercoords.size(), rendercoords.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D) * rendercolors.size(), rendercolors.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
