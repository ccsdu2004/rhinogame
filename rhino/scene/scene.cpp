#include <qopenglfunctions.h>
#include "scene.h"
#include "world.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::resizeGL(int width,int height)
{
	World::getInstance().setViewPort(QSize(width,height));
	auto vp = World::getInstance().getViewPortPos();
	glViewport(vp.x(),vp.y(),width+ vp.x(),height+ vp.y());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,width,0,height,-1,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
