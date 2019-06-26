#pragma once
#include <memory>
#include <QPoint>
#include <QVector>
#include <QFont>
#include "scene.h"
#include "movingSprite.h"
#include "troopMatrix.h"

class MySprite : public MovingSprite
{
public:
	MySprite() :t(0.0f) {}
	bool isMoving() { return t < 1.0f; }

	QVector2D from;
	QVector2D to;
	float   t;
};

class MatrixDemo : public Scene
{
public:
	MatrixDemo();
	~MatrixDemo();
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
	QList<QPointF> getSpritePositions();

	QVector<std::shared_ptr<MySprite>> sprites;
	std::shared_ptr<TroopMatrix> matrix;
	int matrixType;
	bool moving;
};
