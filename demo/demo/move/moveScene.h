#ifndef MOVE_SCENE_H
#define MOVE_SCENE_H
#include <memory>
#include <QTime>
#include "scene.h"
#include "movingSprite.h"
#include "mysprite.h"

class MoveScene : public Scene
{
public:
	MoveScene();
	~MoveScene();
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void mousePressEvent(QMouseEvent* event,int x,int y);
	void mouseMoveEvent(QMouseEvent* event,int x,int y);
	void keyPressEvent(QKeyEvent* event);
private:
	std::shared_ptr<MySprite> sprite;
	bool move;
};

#endif