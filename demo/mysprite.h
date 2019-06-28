#ifndef MYSPRITE_H
#define MYSPRITE_H
#include "movingSprite.h"

class MySprite : public MovingSprite
{
public:
	MySprite() :t(0.0f) {}
	bool isMoving() { return t < 1.0f; }

	QVector2D from;
	QVector2D to;
	float   t;
};

#endif