#ifndef TROOP_MATRIX_RECT5_H
#define TROOP_MATRIX_RECT5_H
#include "troopMatrix.h"

class TroopMatrix_rect5 : public TroopMatrix
{
public:
	TroopMatrix_rect5();
	TroopMatrix_rect5(float sp);

	void setAttirbuteValue(int id, float value);
	float getAttributeValue(int id)const { return span; }

	QList<QPointF> makeMatrix(int width, int height, int count);
private:
	//cx,cy中心坐标,cell:点间距,count:点个数
	QList<QPointF> makeMatrixSub(int cx,int cy,float cell,int count);

	float span;
};

#endif