#include <qopengl.h>
#include <QPainter>
#include <qrandom.h>
#include "world.h"
#include "matrix.h"
#include "rhinoMath.h"
#include <iostream>

#define n (69)
#define TIME 60.0

MatrixDemo::MatrixDemo()
{
	matrixType = TroopMatrix_Rect5;
	matrix = TroopMatrix::createTroopMatrix(TroopMatrix_Rect5);
	matrix->setAttirbuteValue(0,1.0);
	auto list = matrix->makeMatrix(640,480,n);

	for(int i = 0; i < n; i++)
	{
		std::shared_ptr<MySprite> sprite(new MySprite);
		sprite->setSpriteColor(QColor(qrand()%255,qrand()%255,qrand()%255));
		sprite->setSize(QSize(12,12));
		sprite->setPosition(QVector2D(list[i].x(),list[i].y()));
		sprites += sprite;
	}

	moving = false;
}

MatrixDemo::~MatrixDemo()
{
}

void MatrixDemo::initGL()
{
	QColor bgcolor(30,30,120,120);
	World::getInstance().getGLPainter()->setBackgroundColor(bgcolor);
}

void MatrixDemo::glDraw()
{
	glPushMatrix();

	foreach(auto item,sprites)
	{
		item->glDraw();
	}

	glPopMatrix();
}

void MatrixDemo::qtDraw(QWidget* widget)
{

}

void MatrixDemo::update(int time)
{
	for(int i=0;i<n;i++)
	{
		auto item = sprites[i];
		item->update(time);
		float dist1 = 
			rhino::distance2<float>(item->getPosition().x(),item->getPosition().y(),
				item->from.x(),item->from.y());

		float dist2 =
			rhino::distance2<float>(item->to.x(), item->to.y(),
				item->from.x(), item->from.y());

		if (dist1 > dist2)
		{
			item->setVelZero();
			item->setPosition(item->to);
			moving = false;
		}

		sprites[i] = item;
	}
}

void MatrixDemo::mousePressEvent(QMouseEvent* event,int x,int y)
{
	if (moving)
		return;

	if (event->button() == Qt::LeftButton)
	{
		if (matrixType == TroopMatrix_Rect)
		{
			matrix = TroopMatrix::createTroopMatrix(TroopMatrix_Rect5);
			matrix->setAttirbuteValue(0, 1.0);
			auto list = matrix->makeMatrix(640, 480, n);

			for (int i = 0; i < n; i++)
			{
				auto sprite = sprites[i];
				sprite->to = QVector2D(list[i].x(),list[i].y());
				sprite->from = sprites[i]->getPosition();
				sprite->setVel(QVector2D((sprite->to.x() - sprite->from.x()) / TIME,
					(sprite->to.y() - sprite->from.y()) / TIME));
				sprites[i] = sprite;
			}
			matrixType = TroopMatrix_Rect5;
		}
		else
		{
			matrix = TroopMatrix::createTroopMatrix(TroopMatrix_Rect);
			auto list = matrix->makeMatrix(640,480,n);

			for (int i = 0; i < n; i++)
			{
				auto sprite = sprites[i]; 
				sprite->to = QVector2D(list[i].x(),list[i].y());
				sprite->from = sprites[i]->getPosition();
				sprite->setVel(QVector2D((sprite->to.x()- sprite->from.x())/TIME, 
					(sprite->to.y() - sprite->from.y()) / TIME));
				sprites[i] = sprite;
			}
			matrixType = TroopMatrix_Rect;
		}
	}

	moving = true;
}

void MatrixDemo::mouseMoveEvent(QMouseEvent* event,int x,int y)
{
}

void MatrixDemo::keyPressEvent(QKeyEvent* event)
{

}

QList<QPointF> MatrixDemo::getSpritePositions()
{
	QList<QPointF> list;
	foreach(auto item, sprites)
		list += QPointF(item->getPosition().x(),item->getPosition().y());
	return list;
}