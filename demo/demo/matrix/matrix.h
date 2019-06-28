#pragma once
#include <memory>
#include <QPoint>
#include <QVector>
#include <QFont>
#include "scene.h"
#include "movingSprite.h"
#include "mysprite.h"
#include "troopMatrix.h"

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
	void mousePressEvent(QMouseEvent* event,int x,int y);
	void mouseMoveEvent(QMouseEvent* event,int x,int y);
	void keyPressEvent(QKeyEvent* event);
private:
	QList<QPointF> getSpritePositions();

	QVector<std::shared_ptr<MySprite>> sprites;
	std::shared_ptr<TroopMatrix> matrix;
	int matrixType;
	bool moving;
};
