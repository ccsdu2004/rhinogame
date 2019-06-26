#include "flocking.h"
#include "rhinoMath.h"
#include <iostream>

Flocking::Flocking()
{
}

Flocking::Flocking(const QList<std::shared_ptr<MovingSprite>>& sprites) :
boids(sprites)
{
}

Flocking::~Flocking()
{
}

QVector2D Flocking::seek(const QVector2D& target,std::shared_ptr<MovingSprite> sprite)
{
	QVector2D desired = target - sprite->getPosition();
	desired.normalize();
	desired *= maxSpeed;

	auto steer = desired - sprite->getVel();
	rhino::limitVector2D(steer,maxForce);
	return steer;
}

QVector2D Flocking::cohesion(std::shared_ptr<MovingSprite> sprite)
{
	QVector2D steer;

	int count = 0;
	foreach(auto item,boids) 
	{
		if (item->getSpriteID() == sprite->getSpriteID())
			continue;
		float d = sprite->getPosition().distanceToPoint(item->getPosition());
		if (d < maxNeighbordDistance) 
		{
			steer += item->getPosition();
			count++;
		}
	}

	if (count > 0) 
	{
		steer /= float(count);
		return seek(steer,sprite);
	}
	else 
	{
		return QVector2D();
	}
}

QVector2D Flocking::separation(std::shared_ptr<MovingSprite> sprite)
{
	QVector2D steer;
	int count = 0;

	foreach(auto item,boids)
	{
		if (item->getSpriteID() != sprite->getSpriteID())
		{
			float dist = item->getPosition().distanceToPoint(sprite->getPosition());
			if (dist < minSeparation)
			{
				auto diff = sprite->getPosition() - item->getPosition();
				diff.normalize();
				diff /= dist;
				steer += diff;
				count++;
			}
		}
	}

	if (count > 0) 
	{
		steer /= (float)count;
	}

	if (steer.distanceToPoint(QVector2D()) > 1.0)
	{
		steer.normalize();
		steer *= maxSpeed;
		steer -= sprite->getVel();
		rhino::limitVector2D(steer,maxForce);
	}

	return steer;
}

QVector2D Flocking::alignment(std::shared_ptr<MovingSprite> sprite)
{
	QVector2D steer;

	int count = 0;
	foreach(auto item,boids) 
	{
		float d = sprite->getPosition().distanceToPoint(item->getPosition());
		if(item->getSpriteID() != sprite->getSpriteID() && d < maxNeighbordDistance)
		{
			steer += item->getVel();
			count++;
		}
	}

	if (count > 0) 
	{
		steer /= (float)count;
		steer.normalize();
		steer *= maxSpeed;
		steer = steer - sprite->getVel();
		rhino::limitVector2D(steer,maxForce);
		return steer;
	}
	else 
	{
		return steer;
	}
}

void Flocking::applyBorder()
{
	int count = boids.size();
	for (int i = 0; i < count; i++)
	{
		auto pos = boids[i]->getPosition();
		if (pos.x() < borderPos.x()) 
			pos.setX(borderPos.x()+borderSize.width());
		if (pos.y() < 0) 
			pos.setY(borderPos.y()+borderSize.height());
		if (pos.x() > borderPos.x() + borderSize.width())
			pos.setX(0);
		if (pos.y() > borderPos.y() + borderSize.height())
			pos.setY(0);
		boids[i]->setPosition(pos);
	}
}

void Flocking::setBorderArea(const QPoint& pos,const QSize& size)
{
	borderPos = pos;
	borderSize = size;
}

void Flocking::applyBehaviour(int time)
{
	QVector2D rule1, rule2, rule3;

	for (auto& item: boids)
	{
		rule1 = cohesion(item);
		rule2 = separation(item);
		rule3 = alignment(item);

		auto vel = item->getVel();
		auto pos = item->getPosition();
		vel += rule1;
		vel += rule2; 
		vel += rule3;
		item->setVel(vel);
		item->update(time);
	}
}

void Flocking::glDraw()
{
	if (!isVisible())
		return;

	foreach(auto item, boids)
		item->glDraw();
}

void Flocking::qtDraw(QWidget* widget)
{
	Q_UNUSED(widget)
}

void Flocking::update(int time)
{
	applyBehaviour(time);
	applyBorder();
}