#include "entity.h"

Entity::Entity()
{
}

Entity::Entity(const QPointF& position,const QSizeF& isize):
pos(position),
size(isize)
{
}

Entity::Entity(const QRectF& area):
pos(area.left(),area.bottom()),
size(area.width(),area.height())
{
}

Entity::~Entity()
{
}

void Entity::setPosition(const QVector2D& position)
{
	pos = position;
}

QVector2D Entity::getPosition()const
{
	return pos;
}
	
void Entity::setSize(const QSizeF& isize)
{
	size = isize;
}

QSizeF Entity::getSize()const
{
	return size;
}

void Entity::setRotate(qreal r)
{
	rotate = r;
}