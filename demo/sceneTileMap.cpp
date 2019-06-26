#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QImage>
#include "util.h"
#include "world.h"
#include "sceneTileMap.h"
#include <iostream>

SceneTileMap::SceneTileMap() :
col(0),
row(0),
defSprite(new Sprite())
{
}

bool SceneTileMap::loadTileMapFromCSV(const QString& file,bool fromtop)
{
	QString buffer = readAllBufferFromFile(file);
	if (buffer.isEmpty())
		return false;

	QStringList lines = buffer.split("\n");
	if (lines.isEmpty())
		return false;

	row = 0;
	col = 0;

	if(!fromtop)
		std::reverse(lines.begin(),lines.end());

	foreach(auto line,lines)
	{
		auto items = line.split(",");
		if (col == 0 || col == items.size() && col != 0)
		{
			foreach(auto item, items)
			{
				map += item.toInt();
			}
			row++;
		}

		col = items.size();
	}

	if (row == 0)
		return false;
	
	col = map.size() % row;
	if (col != 0)
		return false;

	col = map.size() / row;
	if (row == 0)
		return false;

	int res = World::getInstance().getWorldResolution();
	World::getInstance().setWorldSize(QSize(col*res,row*res));

	defSprite->setSize(QSize(res, res));

	return true;
}

bool SceneTileMap::setDefaultTileImage(std::shared_ptr<QImage> image)
{
	if(!image)
		return false;

	defSprite->setSpriteImage(image);
	return true;
}

bool SceneTileMap::addTileImage(int id,std::shared_ptr<QImage> image)
{
	if (id < 0 || !image)
		return false;

	std::shared_ptr<Sprite> sprite(new Sprite);
	int res = World::getInstance().getWorldResolution();
	sprite->setSize(QSize(res,res));
	sprite->setSpriteImage(image);
	tileSprites.insert(id,sprite);
	return true;
}

void SceneTileMap::initGL()
{
}

void SceneTileMap::qtDraw(QWidget* widget)
{
}

void SceneTileMap::update(int time)
{
}

void SceneTileMap::glDraw()
{
	QSize viewport = World::getInstance().getViewPort();
	QPoint viewportPos = World::getInstance().getViewPortPos();

	int tileSize = World::getInstance().getWorldResolution()/ 2;
	for(int i = 0; i < map.size(); i++)
	{
		int x = (i%col)*tileSize + tileSize/2;
		int y = (i/col)*tileSize + tileSize/2;

		if(x > viewport.width() + viewportPos.x() + tileSize ||
		   y > viewport.height() + viewportPos.y() + tileSize ||
		   x < viewportPos.x() - tileSize ||
		   y < viewportPos.y() - tileSize)
			continue;

		int tileid = map[i];

		if (tileSprites.find(tileid) != tileSprites.end())
		{
			auto sprite = tileSprites[tileid];
			sprite->setPosition(QVector2D(x,y));
			sprite->glDraw();
		}
		else
		{
			defSprite->setPosition(QVector2D(x,y));
			defSprite->glDraw();
		}
	}
}

void SceneTileMap::resizeGL(int width,int height)
{
	Scene::resizeGL(width,height);
}