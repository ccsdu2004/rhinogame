#ifndef MINPATH_H
#define MINPATH_H
#include <QPoint>
#include <QList>
#include <QFont>
#include "scene.h"

class MinPath : public Scene
{
public:
	MinPath();
	~MinPath();
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
private:
	QFont font;
	QPoint lastPos;
	QList<QPoint> points;
	QList<QPoint> drawPoints;
};

#endif
