#include <cmath>
#include <QMouseEvent>
#include <QPainter>
#include "glwidget.h"
#include "glPainter.h"
#include "world.h"
#include "rhinoMath.h"

GLWidget::GLWidget(QWidget* parent):
QOpenGLWidget(parent)
{
	grabKeyboard();
}

GLWidget::~GLWidget()
{
	makeCurrent();
	World::getInstance().getResourceManager()->clearResources();
	doneCurrent();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(120,120);
}

QSize GLWidget::sizeHint() const
{
    return QSize(360,360);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
	World::getInstance().initGL();
}

void GLWidget::paintEvent(QPaintEvent* event)
{
	World::getInstance().update();
	makeCurrent();
	paintGL();
	World::getInstance().qtDraw(this);
	update();
}

void GLWidget::paintGL()
{
	World::getInstance().glDraw();
}

void GLWidget::resizeGL(int width,int height)
{
	World::getInstance().resizeGL(width,height);
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	World::getInstance().mousePressEvent(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
	World::getInstance().mouseMoveEvent(event);
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
	World::getInstance().keyPressEvent(event);
	QOpenGLWidget::keyPressEvent(event);
}