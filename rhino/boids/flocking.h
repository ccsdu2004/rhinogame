#ifndef RHINO_FLOCKING_H
#define RHINO_FLOCKING_H
#include <memory>
#include <limits>
#include <QList>
#include "drawable.h"
#include "movingSprite.h"

class RHINO_EXPORT Flocking : public Drawable
{
public:
	Flocking();
	Flocking(const QList<std::shared_ptr<MovingSprite>>& sprites);
	~Flocking();
public:
	void addSprite(std::shared_ptr<MovingSprite> sprite){boids += sprite;}
	int getSpriteCount()const { return boids.size(); }

	void setMaxSpeed(float speed) { maxSpeed = speed; }
	float getMaxSpeed()const { return maxSpeed; }

	void setMaxForce(float force) { maxForce = force; }
	float getMaxForce()const { return maxForce; }

	void setMaxNeighbordDistance(float distance) { maxNeighbordDistance = distance; }
	float getMaxNeighbordDistance()const { return maxNeighbordDistance; }

	void setMinSeparation(float separation) { minSeparation = separation; }
	float getMinSeparation()const { return minSeparation; }

	void setBorderArea(const QPoint& pos,const QSize& size);
public:
	void applyBehaviour(int time);
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
private:
	QVector2D seek(const QVector2D& target,std::shared_ptr<MovingSprite> sprite);
	QVector2D cohesion(std::shared_ptr<MovingSprite> sprite);
	QVector2D separation(std::shared_ptr<MovingSprite> sprite);
	QVector2D alignment(std::shared_ptr<MovingSprite> sprite);
	void applyBorder();
private:
	QList<std::shared_ptr<MovingSprite>> boids;
	float maxSpeed = std::numeric_limits<float>::max();
	float maxForce = std::numeric_limits<float>::max();
	float maxNeighbordDistance = 48.0f;
	float minSeparation = 6.0;
	QPoint borderPos = QPoint(0,0);
	QSize borderSize = QSize(640,480);
};

#endif