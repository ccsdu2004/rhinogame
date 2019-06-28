#include <qopengl.h>
#include "world.h"
#include "tileScene.h"
#include <iostream>
#include <QTime>
#include <QPainter>

TileScene::TileScene()
{
	tileMap = SceneTileMap::createTileMap(6);
}

TileScene::~TileScene()
{
}

void TileScene::initGL()
{
	bool loaded = tileMap->loadTileMapFromCSV("data/desert.csv",false);
	std::cout << "load:"<<loaded << std::endl;

	glShadeModel(GL_FLAT);

	auto tiles = QImage("data/tmw_desert_spacing.png");
	//auto tiles = QImage("tile/grass.png");

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

void TileScene::mousePressEvent(QMouseEvent* event,int x,int y)
{
	static bool showGrid = false;
	if (event->button() == Qt::LeftButton)
	{
		World::getInstance().getGridCellManager()->setGridCellVisible(showGrid = !showGrid);
	}

	event->ignore();
}

void TileScene::mouseMoveEvent(QMouseEvent* event,int x,int y)
{
}

void TileScene::keyPressEvent(QKeyEvent* event)
{
}
