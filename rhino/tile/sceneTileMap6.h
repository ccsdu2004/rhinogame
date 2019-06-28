#ifndef RHINO_SCENETILEMAP6_H
#define RHINO_SCENETILEMAP6_H
#include "sceneTileMap.h"

class SceneTileMap6 : public SceneTileMap
{
public:
	SceneTileMap6() = default;
	~SceneTileMap6() = default;
public:
	bool loadTileMapFromCSV(const QString& file,bool fromtop);
	int  getTileIDByTilePos(int x, int y);
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
};

#endif