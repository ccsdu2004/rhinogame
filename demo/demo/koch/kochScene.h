#ifndef KOCH_SCENE_H
#define KOCH_SCENE_H
#include "scene.h"

class KochScene : public Scene
{
public:
	KochScene();
	~KochScene();
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
private:
	void drawKoch(const QVector2D& beg,const QVector2D& end,int depth,bool left);
};



#endif