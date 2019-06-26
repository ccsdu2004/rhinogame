#ifndef DEMO_BOIDS_H
#define DEMO_BOIDS_H
#include <memory>
#include <QPoint>
#include <QList>
#include <QFont>
#include "scene.h"
#include "movingSprite.h"
#include "boids/flocking.h"

class Boids : public Scene
{
public:
	Boids();
	~Boids();
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void resizeGL(int w,int h);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
public:
	void setMaxSpeed(int v);
	void setMaxForce(int v);
	void setMinNeighbordDistance(int v);
	void setMinSeparation(int v);
private:
	std::shared_ptr<Flocking> flocking;
};


#endif