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
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
private:
	std::unique_ptr<SceneTileMap> tileMap;
};



#endif