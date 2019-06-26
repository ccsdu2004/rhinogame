#ifndef RHINO_GRIDCELL_MANAGER_H
#define RHINO_GRIDCELL_MANAGER_H
#include <QPoint>
#include <QLine>
#include <QList>
#include <QColor>
#include "rhino.h"

class RHINO_EXPORT GridCellManager
{
public:
	virtual ~GridCellManager() {}
public:	
	void setGridCellColor(const QColor& color);
	QColor getGridCellColor()const;

	void setGridCellVisible(bool visible);
	bool isGridCellVisible()const;
	void drawGridCell();
public:
#define GridCellManager_CellMode4 0
#define GridCellManager_CellMode6 1
	virtual int getCellMode()const = 0;
	virtual QPoint getCellCoordinateByWorldPos(int x, int y) = 0;
	virtual QPointF getWorldPosByCellCoordinate(int x, int y) = 0;
	virtual int getAdjacentCell(int x, int y, QPoint* points) = 0;
	QList<QLine> getAdjacentCellsInMap(int width, int height, const QList<QPoint>& miss = QList<QPoint>());
private:
	bool gridCellVisible;
	QColor gridCellColor;
};

#endif