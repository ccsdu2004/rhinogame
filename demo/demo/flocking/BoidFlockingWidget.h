#ifndef BOID_FLOCKING_WIDGET_H
#define BOID_FLOCKING_WIDGET_H
#include <QSlider>
#include "glwidget.h"
#include "demo/flocking/boids.h"

class BoidFlockingWidget : public QWidget
{
	Q_OBJECT
public:
	BoidFlockingWidget(QWidget* parent = nullptr);
public slots:
	void setMaxSpeed(int v);
	void setMaxForce(int v);
	void setMinNeighbordDistance(int v);
	void setMinSeparation(int v);
private:
	GLWidget* glWidget;
	QSlider* maxSpeedSlider;
	QSlider* maxForceSlider;
	QSlider* minNeighbordDistanceSlider;
	QSlider* minSeparationSlider;

	std::shared_ptr<Boids> scene;
};


#endif