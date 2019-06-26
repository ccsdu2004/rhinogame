#include "rhinoMath.h"
#include "movingSprite.h"

MovingSprite::MovingSprite()
{
}

MovingSprite::MovingSprite(const QPointF& position,const QSizeF& size) :
Sprite(position, size)
{
}

MovingSprite::MovingSprite(const QPointF& position,const QSizeF& size,std::shared_ptr<QImage> image):
Sprite(position,size,image)
{
}

MovingSprite::MovingSprite(std::shared_ptr<QImage> image):
Sprite(image)
{
}

MovingSprite::~MovingSprite()
{
}

void MovingSprite::setAcclerateZero()
{
	acc = QVector2D(0,0);
}

void MovingSprite::setAcclerate(const QVector2D& ac)
{
	acc = ac;
}

void MovingSprite::setVelZero()
{
	vel = QVector2D(0,0);
}

void MovingSprite::setVel(const QVector2D& v)
{
	vel = v;
}

bool MovingSprite::isMoving()const
{
	return rhino::isZero(vel.x()) && rhino::isZero(vel.y());
}

void MovingSprite::update(int time)
{
	auto position = getPosition();
	auto offset = vel*(float)time;
	position += QVector2D(offset.x(),offset.y());
	setPosition(position);

	auto delta = acc*(float)time;
	vel += QVector2D(delta.x(),delta.y());
}