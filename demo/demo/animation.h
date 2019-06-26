#pragma once
#include <memory>
#include <QPoint>
#include <QList>
#include <QFont>
#include "scene.h"
#include "movingSprite.h"

class Animation : public Scene
{
public:
	Animation();
	~Animation();
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
	std::shared_ptr<MovingSprite> sprite;
};
