#ifndef RHINO_SCENETILEMAP4_H
#define RHINO_SCENETILEMAP4_H
#include "sceneTileMap.h"

class SceneTileMap4 : public SceneTileMap
{
public:
	SceneTileMap4() = default;
	~SceneTileMap4() = default;
public:
	bool loadTileMapFromCSV(const QString& file,bool fromtop);
	int  getTileIDByTilePos(int x,int y);
public:
	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
};

#endif