#include "sceneManagerPriv.h"

void SceneManagerPriv::initGL()
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->initGL();
}
 
void SceneManagerPriv::glDraw()
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->glDraw();
}

void SceneManagerPriv::qtDraw(QWidget* widget)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->qtDraw(widget);
}

void SceneManagerPriv::update(int time)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->update(time);
}

void SceneManagerPriv::resizeGL(int width,int height)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->resizeGL(width,height);
}

void SceneManagerPriv::mousePressEvent(QMouseEvent* event)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->mousePressEvent(event);
}

void SceneManagerPriv::mouseMoveEvent(QMouseEvent* event)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->mouseMoveEvent(event);
}

void SceneManagerPriv::keyPressEvent(QKeyEvent* event)
{
	auto scene = getCurrentScene();
	if (scene == nullptr)
		return;

	scene->keyPressEvent(event);
}