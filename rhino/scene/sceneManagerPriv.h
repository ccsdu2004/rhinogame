#ifndef RHINO_SCENEMANAGER_H
#define RHINO_SCENEMANAGER_H
#include "sceneManager.h"

class SceneManagerPriv : public SceneManager
{
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void resizeGL(int width,int height);
	void mousePressEvent(QMouseEvent* event,int x,int y);
	void mouseMoveEvent(QMouseEvent* event,int x,int y);
	void keyPressEvent(QKeyEvent* event);
};

#endif