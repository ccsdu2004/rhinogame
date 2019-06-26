#include "gridCell6Manager.h"
#include "world.h"
#include "rhinoMath.h"

int GridCell6Manager::getCellMode()const 
{
	return GridCellManager_CellMode6;
}

int GridCell6Manager::getAdjacentCell(int x,int y,QPoint* points)
{
	points[0] = QPoint(x-1,y);
	points[1] = QPoint(x+1,y);
	points[2] = QPoint(x,y-1);
	points[3] = QPoint(x,y+1);

	if(x % 2 == 1)
	{
		points[4] = QPoint(x-1,y+1);
		points[5] = QPoint(x+1,y+1);
	}
	else 
	{
		points[4] = QPoint(x-1,y-1);
		points[5] = QPoint(x+1,y-1);
	}

	return 6;
}

#define res World::getInstance().getWorldResolution() 

QPointF GridCell6Manager::getWorldPosByCellCoordinate(int x,int y)
{
	if (x % 2 == 0)
		return QPointF(1.5f*res*(x+1),
			(0.5*R3+R3*y)*res);
	return QPointF(1.5f*res*(x + 1),
		(R3 + y * R3)*res);
}

QPoint GridCell6Manager::getCellCoordinateByWorldPos(int x,int y)
{
	QPoint point(-1,-1);
	float xpos = x-res*0.5f;
	float ypos = y/(R3*res) - 0.5f;

	int yset[2] = {std::floorf(ypos),std::ceilf(ypos)};

	xpos /= (1.5*World::getInstance().getWorldResolution());
	int xset[2] = { std::floorf(xpos),std::ceilf(xpos)};

	auto p00 = getWorldPosByCellCoordinate(xset[0],yset[0]);
	auto p01 = getWorldPosByCellCoordinate(xset[0],yset[1]);
	auto p10 = getWorldPosByCellCoordinate(xset[1],yset[0]);
	auto p11 = getWorldPosByCellCoordinate(xset[1],yset[1]);

	float d00 = rhino::distance2<float>(x,y,p00.x(),p00.y());
	float d01 = rhino::distance2<float>(x,y,p01.x(),p01.y());
	float d10 = rhino::distance2<float>(x,y,p10.x(),p10.y());
	float d11 = rhino::distance2<float>(x,y,p11.x(),p11.y());

	int i,j;
	if(d00 < d01 && d00 < d10 && d00 < d11)
	{
		i = xset[0];
		j = yset[0];
	}
	else if(d00 > d01 && d01 < d10 && d01 < d11)
	{
		i = xset[0];
		j = yset[1];
	}
	else if(d10 < d00 && d10 < d01 && d10 < d11)
	{
		i = xset[1];
		j = yset[0];
	}
	else
	{
		i = xset[1];
		j = yset[1];
	}

	return QPoint(i,j);
}