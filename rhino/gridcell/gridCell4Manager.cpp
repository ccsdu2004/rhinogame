#include <cmath>
#include "gridCell4Manager.h"
#include "world.h"
#include "rhinoMath.h"

int GridCell4Manager::getCellMode()const 
{
	return GridCellManager_CellMode4; 
}

int GridCell4Manager::getAdjacentCell(int x,int y,QPoint* points)
{
	points[0] = QPoint(x-1,y);
	points[1] = QPoint(x+1,y);
	points[2] = QPoint(x,y-1);
	points[3] = QPoint(x,y+1);
	return 4;
}

#define res World::getInstance().getWorldResolution() 

QPointF GridCell4Manager::getWorldPosByCellCoordinate(int x,int y)
{
	return QPointF(res*x+0.5*res,res*y+0.5*res);
}

QPoint GridCell4Manager::getCellCoordinateByWorldPos(int x, int y)
{
	return QPoint(std::floor(x/res), std::floor(y / res));
}

#undef res