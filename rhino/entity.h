#ifndef RHINO_ENTITY_H
#define RHINO_ENTITY_H
#include <QPoint>
#include <QVector2D>
#include <QSize>
#include <QRect>
#include "rhino.h"

class RHINO_EXPORT Entity
{
public:
	Entity();
	Entity(const QPointF& position,const QSizeF& size);
	Entity(const QRectF& area);
	virtual ~Entity();
public:
	void setPosition(const QVector2D& position);
	QVector2D getPosition()const;
	
	void setSize(const QSizeF& size);
	QSizeF getSize()const;

	void setRotate(qreal r);
	qreal getRotate()const { return rotate; }
protected:
	QVector2D pos;
	QSizeF size;
	qreal rotate;
};

#endif