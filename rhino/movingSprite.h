#ifndef RHINO_MOVINGSPRITE_H
#define RHINO_MOVINGSPRITE_H
#include <QVector2D>
#include "sprite.h"

class RHINO_EXPORT MovingSprite : public Sprite
{
public:
	MovingSprite();
	explicit MovingSprite(const QPointF& position,const QSizeF& size);
	explicit MovingSprite(const QPointF& position,const QSizeF& size,std::shared_ptr<QImage> image);
	explicit MovingSprite(std::shared_ptr<QImage> image);
	virtual ~MovingSprite();
public:
	void setAcclerateZero();
	void setAcclerate(const QVector2D& ac);
	QVector2D getAcclerate()const { return acc; }

	void setVelZero();
	void setVel(const QVector2D& v);
	QVector2D getVel()const { return vel; }
	bool isMoving()const;

	void update(int time);
private:
	QVector2D acc;
	QVector2D vel;
};

#endif