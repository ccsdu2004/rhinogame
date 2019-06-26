#ifndef RHINO_GRIDCELL6_MANAGER_H
#define RHINO_GRIDCELL6_MANAGER_H
#include "gridCellManger.h"

class GridCell6Manager : public GridCellManager
{
public:
	int getCellMode()const;
	QPoint getCellCoordinateByWorldPos(int x, int y);
	QPointF getWorldPosByCellCoordinate(int x, int y);
	int getAdjacentCell(int x, int y, QPoint* points);
};

#endif