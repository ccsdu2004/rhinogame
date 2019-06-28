#include <QFile>
#include <QDebug>
#include <QTextStream>
#include "util.h"
#include "world.h"
#include "sceneTileMap6.h"

bool SceneTileMap6::loadTileMapFromCSV(const QString& file,bool fromtop)
{
	QString buffer = readAllBufferFromFile(file);
	if (buffer.isEmpty())
		return false;

	QStringList lines = buffer.split("\n");
	if (lines.isEmpty())
		return false;

	row = 0;
	col = 0;

	if (!fromtop)
		std::reverse(lines.begin(),lines.end());

	terrain.clear();

	foreach(auto line,lines)
	{
		auto items = line.split(",");
		if (col == 0 || col == items.size() && col != 0)
		{
			foreach(auto item, items)
			{
				terrain += item.toInt();
			}
			row++;
		}

		col = items.size();
	}

	if (row == 0)
		return false;

	col = terrain.size() % row;
	if (col != 0)
		return false;

	col = terrain.size() / row;
	if (row == 0)
		return false;

	int res = World::getInstance().getWorldResolution();
	World::getInstance().setWorldSize(QSize(col*res, row*res));

	defSprite->setSize(QSize(res,res));

	return true;
}

int SceneTileMap6::getTileIDByTilePos(int x, int y)
{
	int index = x * col + y;
	if (index < 0 || index >= terrain.size())
		return -1;
	return terrain[index];
}

void SceneTileMap6::initGL()
{
}

void SceneTileMap6::glDraw()
{
	int tileSize = World::getInstance().getWorldResolution();
	for (int i = 0; i < terrain.size(); i++)
	{
		int x = (i%col)*tileSize + tileSize / 2;
		int y = (i / col)*tileSize + tileSize / 2;

		if(!World::getInstance().getViewport()->isContain(x, y))
			continue;

		int tileid = terrain[i];

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

void SceneTileMap6::qtDraw(QWidget* widget)
{
}

void SceneTileMap6::update(int time)
{
}
