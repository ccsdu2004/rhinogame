#include <QLabel>
#include <QGridLayout>
#include "world.h"
#include "BoidFlockingWidget.h"

BoidFlockingWidget::BoidFlockingWidget(QWidget* parent) :
	QWidget(parent)
{
	auto grid = new QGridLayout(this);
	glWidget = new GLWidget(this);
	grid->addWidget(glWidget, 0, 0, 1, 2);

	grid->addWidget(new QLabel("maxSpeed"),1,0,1,1);
	grid->addWidget(maxSpeedSlider = new QSlider(Qt::Horizontal),1,1,1,1);
	maxSpeedSlider->setRange(1,100);
	maxSpeedSlider->setValue(20);

	grid->addWidget(new QLabel("maxForce"), 2, 0, 1, 1);
	grid->addWidget(maxForceSlider = new QSlider(Qt::Horizontal), 2, 1, 1, 1);
	maxForceSlider->setRange(1, 100);
	maxForceSlider->setValue(20);

	grid->addWidget(new QLabel("minNeighbordDistance"), 3, 0, 1, 1);
	grid->addWidget(minNeighbordDistanceSlider = new QSlider(Qt::Horizontal), 3, 1, 1, 1);
	minNeighbordDistanceSlider->setRange(1, 100);
	minNeighbordDistanceSlider->setValue(20);

	grid->addWidget(new QLabel("minSeparation"), 4, 0, 1, 1);
	grid->addWidget(minSeparationSlider = new QSlider(Qt::Horizontal), 4, 1, 1, 1);
	minSeparationSlider->setRange(1, 100);
	minSeparationSlider->setValue(20);

	World::getInstance().init(GridCellManager_CellMode6,"rhino.log");
	World::getInstance().setWorldResolution(12);

	World::getInstance().getGridCellManager()->setGridCellVisible(true);

	QFont font;
	font.setPointSize(9);
	World::getInstance().getResourceManager()->setSpriteFont(font);

	scene.reset(new Boids());
	World::getInstance().getSceneManager()->addSceneAsCurrent(scene);

	World::getInstance().getGridCellManager()->setGridCellVisible(true);

	connect(maxSpeedSlider,SIGNAL(valueChanged(int)),this,SLOT(setMaxSpeed(int)));
	connect(maxForceSlider, SIGNAL(valueChanged(int)), this, SLOT(setMaxForce(int)));
	connect(minNeighbordDistanceSlider, SIGNAL(valueChanged(int)), this, SLOT(setMinNeighbordDistance(int)));
	connect(minSeparationSlider, SIGNAL(valueChanged(int)), this, SLOT(setMinSeparation(int)));
}

void BoidFlockingWidget::setMaxSpeed(int v)
{
	scene->setMaxSpeed(v);
}

void BoidFlockingWidget::setMaxForce(int v)
{
	scene->setMaxForce(v);
}

void BoidFlockingWidget::setMinNeighbordDistance(int v)
{
	scene->setMinNeighbordDistance(v);
}

void BoidFlockingWidget::setMinSeparation(int v)
{
	scene->setMinSeparation(v);
}