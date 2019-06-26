#include "rhinoMath.h"
#include "troopMatrix_rect5.h"

TroopMatrix_rect5::TroopMatrix_rect5():
span(0.5)
{
}

void TroopMatrix_rect5::setAttirbuteValue(int id,float sp)
{
	span = rhino::clamp<float>(sp,0.2,1.0);
}

QList<QPointF> TroopMatrix_rect5::makeMatrixSub(int cx,int cy,float cell,int count)
{
	int col = sqrt(count);
	if(col*col != count)
		col++;

	float width = 0.5*cell*col;

	QList<QPointF> list;

	for(int i = 0; i < count; i++)
	{
		QPointF point;
		point.setX(-width+(i%col)*cell+cx+0.5*cell);
		point.setY(-width+(i/col)*cell+cy+0.5*cell);
		list.push_back(point);
	}

	return list;
}

QList<QPointF> TroopMatrix_rect5::makeMatrix(int width,int height,int count)
{
	int edge = std::min(width,height);
	int unitcount = count % 5;
	if (unitcount != 0)
		unitcount = (unitcount + count) / 5;
	else
		unitcount = count / 5;

	float unitsize = edge/(3.0 + 2*span);
	int unitcol = sqrt(unitcount);
	if (unitcol*unitcol != unitcount)
		unitcol++;

	float cellsize = unitsize / (unitcol-1);

	float cx = width*0.5;
	float cy = height*0.5;

	QList<QPointF> list;
	list += makeMatrixSub(cx,cy,cellsize,count - 4*unitcount);
	list += makeMatrixSub(cx-unitsize*(1.0+span),cy,cellsize,unitcount);
	list += makeMatrixSub(cx+unitsize*(1.0+span),cy,cellsize,unitcount);
	list += makeMatrixSub(cx,cy+unitsize*(1.0+span),cellsize,unitcount);
	list += makeMatrixSub(cx,cy-unitsize*(1.0+span),cellsize,unitcount);
	return list;
}