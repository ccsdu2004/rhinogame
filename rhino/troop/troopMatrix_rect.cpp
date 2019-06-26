#include <cmath>
#include "troopMatrix_rect.h"

QList<QPointF> TroopMatrix_rect::makeMatrix(int width,int height,int count)
{
	QList<QPointF> list;
	int edge = std::min(width,height);
	int col = sqrt(count);
	if(col*col != count)
		col++;

	float distance = edge / (float)col;
	float xoff = 0.5*(width - (col-1)*distance);
	float yoff = 0.5*(height-(col-1)*distance);

	for (int i = 0; i < count; i++)
	{
		QPointF point;
		point.setX(xoff+(i%col)*distance);
		point.setY(yoff+(i/col)*distance);
		list.push_back(point);
	}

	return list;
}