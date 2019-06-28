#include <qopengl.h>
#include <QTime>
#include <QPainter>
#include "world.h"
#include "moveScene.h"
#include "rhinoMath.h"
#include <iostream>

MoveScene::MoveScene():
sprite(new MySprite()),
move(false)
{
}

MoveScene::~MoveScene()
{
}

void MoveScene::initGL()
{
	auto size = World::getInstance().getWorldResolution();
	sprite->setSize(QSize(size,size));
	sprite->setSpriteColor(QColor(qrand()%255,qrand()%255,qrand()%240));
}

void MoveScene::glDraw()
{
	sprite->glDraw();
}

void MoveScene::qtDraw(QWidget* widget)
{
	QPainter painter(widget);
	painter.setPen(QPen(Qt::blue));
	int fps = World::getInstance().getFPS();
	painter.drawText(10,20,QString("fps:%1").arg(fps));
}

void MoveScene::update(int time)
{
	sprite->update(time);
	float dist1 =
		rhino::distance2<float>(sprite->getPosition().x(), sprite->getPosition().y(),
			sprite->from.x(), sprite->from.y());

	float dist2 =
		rhino::distance2<float>(sprite->to.x(), sprite->to.y(),
			sprite->from.x(), sprite->from.y());

	if (dist1 > dist2)
	{
		sprite->setVelZero();
		sprite->setPosition(sprite->to);
		move = false;
	}
}

void MoveScene::mousePressEvent(QMouseEvent* event,int x,int y)
{
	if (event->button() == Qt::LeftButton)
	{
		if (move)
			return;

		auto gridPos = World::getInstance().getGridCellManager()->getCellCoordinateByWorldPos(x,y);
		auto spritePos = World::getInstance().getGridCellManager()->getCellCoordinateByWorldPos(sprite->getPosition().x(),sprite->getPosition().y());
		if (gridPos == spritePos)
			return;

		move = true;
		auto pos = World::getInstance().getGridCellManager()->getWorldPosByCellCoordinate(gridPos.x(),gridPos.y());
		sprite->from = sprite->getPosition();
		sprite->to = QVector2D(pos.x(),pos.y());
		sprite->setVel(QVector2D((sprite->to.x() - sprite->from.x()) / 60.0,
			(sprite->to.y() - sprite->from.y()) / 60.0));
	}
}

void MoveScene::mouseMoveEvent(QMouseEvent* event,int x,int y)
{
}

void MoveScene::keyPressEvent(QKeyEvent* event)
{
}
