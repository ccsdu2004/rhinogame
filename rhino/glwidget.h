#ifndef RHINO_GLWIDGET_H
#define RHINO_GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "rhino.h"

class RHINO_EXPORT GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
public:
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
protected:
    void initializeGL() override;
    void paintGL()override;
	void paintEvent(QPaintEvent* event)override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent* event)override;
private:
};

#endif
