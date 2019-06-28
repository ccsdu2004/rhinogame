#ifndef TILE_SCENE_H
#define TILE_SCENE_H
#include <memory>
#include <QTime>
#include "scene.h"
#include "sprite.h"
#include "sceneTileMap.h"

class TileScene : public Scene
{
public:
	TileScene();
	~TileScene();
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void mousePressEvent(QMouseEvent* event, int x, int y);
	void mouseMoveEvent(QMouseEvent* event, int x, int y);
	void keyPressEvent(QKeyEvent* event);
private:
	std::shared_ptr<SceneTileMap> tileMap;
};



#endif