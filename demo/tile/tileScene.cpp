#include <qopengl.h>
#include "world.h"
#include "tileScene.h"
#include <iostream>
#include <QTime>
#include <QPainter>

TileScene::TileScene()
{
	tileMap.reset(new SceneTileMap());
}

TileScene::~TileScene()
{
}

void TileScene::initGL()
{
	bool loaded = tileMap->loadTileMapFromCSV("data/desert.csv");
	std::cout << "load:"<<loaded << std::endl;

	glShadeModel(GL_FLAT);

	auto tiles = QImage("data/tmw_desert_spacing.png");

	auto resMgr = World::getInstance().getResourceManager();

	for (int i = 0; i < 48; i++)
	{
		int x = i % 8;
		int y = i / 8;
		auto image = tiles.copy(x*32+(1+x),y*32+(1+y),32,32);
		std::shared_ptr<QImage> ptr = std::make_shared<QImage>(std::move(image));
		tileMap->addTileImage(i,ptr);
	}
}

void TileScene::glDraw()
{
	glEnable(GL_TEXTURE_2D);
	tileMap->glDraw();
	glDisable(GL_TEXTURE_2D);
}

void TileScene::qtDraw(QWidget* widget)
{
	QPainter painter(widget);
	painter.setPen(QPen(Qt::blue));
	int fps = World::getInstance().getFPS();
	painter.drawText(10,20,QString("fps:%1").arg(fps));
}

void TileScene::update(int time)
{
}

void TileScene::mousePressEvent(QMouseEvent* event)
{

}

void TileScene::mouseMoveEvent(QMouseEvent* event)
{
}

void TileScene::keyPressEvent(QKeyEvent* event)
{
}
