#include <qopengl.h>
#include <QPainter>
#include "world.h"
#include "boids.h"
#include <vector>
#include <qrandom.h>

Boids::Boids():
flocking(new Flocking())
{
}

Boids::~Boids()
{
}

void Boids::initGL()
{
	glShadeModel(GL_FLAT);

	flocking->setMaxForce(2.0);
	flocking->setMaxNeighbordDistance(4.0);
	flocking->setMaxSpeed(12.0);
	flocking->setMinSeparation(2.4);
	flocking->setBorderArea(QPoint(-10,-10),QSize(660,500));
	
	auto image = World::getInstance().getResourceManager()->loadImage("data/flare.png");

	for (int i = 0; i < 10; i++)
	{
		auto sprite = std::shared_ptr<MovingSprite>(new MovingSprite(image));
		sprite->setPosition(QVector2D(qrand()%640,qrand()%480));
		sprite->setVel(QVector2D(0.2*((qrand() % 9)-4),0.2*((qrand() %9)-4)));
		sprite->setSize(QSize(16,16));
		sprite->setSpriteID(i);
		flocking->addSprite(sprite);
	}
}

void Boids::glDraw()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	flocking->glDraw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Boids::qtDraw(QWidget* widget)
{
}

void Boids::update(int time)
{
	flocking->update(time*0.6);
}

void Boids::resizeGL(int w, int h)
{
	Scene::resizeGL(w, h);
	flocking->setBorderArea(QPoint(-10,-10),QSize(w+20,h+20));
}

void Boids::mousePressEvent(QMouseEvent* event)
{

}

void Boids::mouseMoveEvent(QMouseEvent* event)
{
}

void Boids::keyPressEvent(QKeyEvent* event)
{

}

void Boids::setMaxSpeed(int v)
{
	float d = v * 0.01;
	flocking->setMaxSpeed(d);
}

void Boids::setMaxForce(int v)
{
	float d = v * 0.05;
	flocking->setMaxForce(d);
}

void Boids::setMinNeighbordDistance(int v)
{
	float d = v*0.3;
	flocking->setMaxNeighbordDistance(d);
}

void Boids::setMinSeparation(int v)
{
	float d = v * 0.2;
	flocking->setMinSeparation(d);
}