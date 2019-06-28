#include "world.h"
#include "sceneTileMap.h"
#include "sceneTileMap4.h"
#include "sceneTileMap6.h"

std::shared_ptr<SceneTileMap> SceneTileMap::createTileMap(int type)
{
	if (type == 4)
		return std::make_shared<SceneTileMap4>();
	else if (type == 6)
		return std::make_shared<SceneTileMap6>();
	return nullptr;
}

SceneTileMap::SceneTileMap():
row(0),
col(0),
defSprite(new Sprite())
{
	defSprite->setSpriteColor(QColor(Qt::blue));
}

bool SceneTileMap::setDefaultTileImage(std::shared_ptr<QImage> image)
{
	if (!image)
		return false;

	defSprite->setSpriteImage(image);
	return true;
}

bool SceneTileMap::addTileImage(int id, std::shared_ptr<QImage> image)
{
	if (id < 0 || !image)
		return false;

	std::shared_ptr<Sprite> sprite(new Sprite);
	int res = World::getInstance().getWorldResolution();
	sprite->setSize(QSize(res, res));
	sprite->setSpriteImage(image);
	tileSprites.insert(id, sprite);
	return true;
}

void SceneTileMap::clear()
{
	col = row = 0;
	tileSprites.clear();
	terrain.clear();
}