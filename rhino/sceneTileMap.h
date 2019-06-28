#ifndef RHINO_SCENETILEMAP_H
#define RHINO_SCENETILEMAP_H
#include <memory>
#include <QVector>
#include <QImage>
#include <QMap>
#include "rhino.h"
#include "sprite.h"
#include "drawable.h"

class RHINO_EXPORT SceneTileMap : public Drawable
{
public:
	static std::shared_ptr<SceneTileMap> createTileMap(int type);
#define SceneMap_Tile_NA   -1
#define SceneMap_Tile_DEF   0
#define SceneMap_Tile_SEA   1
#define SceneMap_Tile_ROAD  2
#define SceneMap_Tile_CITY  3
#define SceneMap_Tile_GRASS 4
#define SceneMap_Tile_SNOW  5
public:
	SceneTileMap();
	virtual ~SceneTileMap() = default;
public:
	virtual bool loadTileMapFromCSV(const QString& file,bool fromtop = false) = 0;

	bool setDefaultTileImage(std::shared_ptr<QImage> tile);
	bool addTileImage(int id, std::shared_ptr<QImage> tile);

	virtual int getTileIDByTilePos(int x,int y) = 0;

	void clear();
public:
	virtual void glDraw() = 0;
protected:
	int col,row;
	std::shared_ptr<Sprite> defSprite;
	QMap<int,std::shared_ptr<Sprite>> tileSprites;
	QVector<int> terrain;
};

#endif