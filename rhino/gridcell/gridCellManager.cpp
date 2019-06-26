#include "gridCellManger.h"
#include "rhinoMath.h"
#include "world.h"

namespace
{

bool hasThisPoint(const QList<QLine>& list, const QPoint& point1, const QPoint& point2)
{
	auto itr = qFind(list, QLine(point1, point2));
	if (itr != list.end())
		return true;

	itr = qFind(list, QLine(point2, point1));
	if (itr != list.end())
		return true;
	return false;
}

}

//TODO:使用list性能不好
QList<QLine> GridCellManager::getAdjacentCellsInMap(int width,int height,const QList<QPoint>& miss)
{
	QList<QLine> output;

	QPoint points[6];

#define DO_IT(k)\
	if(!hasThisPoint(output,QPoint(i,j),points[k]))\
        if(i>=0 && j >= 0 && points[k].x() >= 0 && points[k].y() >= 0)\
if(points[k].x() <= width)\
if(points[k].y() <= height)\
if(!miss.contains(QPoint(i,j)))\
if(!miss.contains(points[k]))\
		    output.push_back(QLine(QPoint(i,j),points[k]));

	for(int i=0;i<=width;i++)
		for(int j = 0; j <= height; j++)
		{
			getAdjacentCell(i,j,points);
			if (getCellMode() == GridCellManager_CellMode4)
			{
				DO_IT(0)
				DO_IT(1)
				DO_IT(2)
				DO_IT(3)
			}
			else if (getCellMode() == GridCellManager_CellMode6)
			{
				DO_IT(0)
				DO_IT(1)
				DO_IT(2)
				DO_IT(3)
				DO_IT(4)
				DO_IT(5)
			}
		}

	return output;
}

void GridCellManager::setGridCellColor(const QColor& color)
{
	gridCellColor = color;
}

QColor GridCellManager::getGridCellColor()const
{
	return gridCellColor;
}

void GridCellManager::setGridCellVisible(bool visible)
{
	gridCellVisible = visible;
}

bool GridCellManager::isGridCellVisible()const
{
	return gridCellVisible;
}

void GridCellManager::drawGridCell()
{
	if(!gridCellVisible)
		return;

	GLScopedColor scoped;
	{
		float cellsize = World::getInstance().getWorldResolution();
		auto worldSize = World::getInstance().getWorldSize();
		auto painter = World::getInstance().getGLPainter();
		painter->setColor(gridCellColor);
		if(getCellMode() == GridCellManager_CellMode6)
		{
			int col = 2*worldSize.width()/cellsize;
			int row = R3*worldSize.height()/cellsize;
			painter->drawHexGons(0,0,cellsize,col,row);
		}
		else if(getCellMode() == GridCellManager_CellMode4)
		{
			int col = worldSize.width() / cellsize;
			int row = worldSize.height() / cellsize;
			painter->drawGrid(0,0,cellsize,cellsize,col+10,row);
		}
	}
}