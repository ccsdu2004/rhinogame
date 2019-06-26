#ifndef RHINO_SCENETILEMAP_H
#define RHINO_SCENETILEMAP_H
#include <memory>
#include <QVector>
#include <QImage>
#include "sprite.h"

class SceneTileMap : public Scene
{
#define SceneMap_Tile_NA   -1
#define SceneMap_Tile_DEF   0
#define SceneMap_Tile_SEA   1
#define SceneMap_Tile_ROAD  2
#define SceneMap_Tile_CITY  3
#define SceneMap_Tile_GRASS 4
#define SceneMap_Tile_SNOW  5
public:
	SceneTileMap();
	~SceneTileMap() = default;
public:
	bool loadTileMapFromCSV(const QString& file,bool fromtop = false);
	
	bool setDefaultTileImage(std::shared_ptr<QImage> tile);
	bool addTileImage(int id,std::shared_ptr<QImage> tile);

	void initGL();
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
public:
	void resizeGL(int width,int height);
private:
	int col,row;
	std::shared_ptr<Sprite> defSprite;
	QMap<int,std::shared_ptr<Sprite>> tileSprites;
	QVector<int> map;
};

#endif