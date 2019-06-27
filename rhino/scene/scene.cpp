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
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,width,0,height,-1,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
