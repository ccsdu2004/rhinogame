#ifndef TROOP_MATRIX_RECT_H
#define TROOP_MATRIX_RECT_H
#include "troopMatrix.h"

class TroopMatrix_rect : public TroopMatrix
{
public:
	void setAttirbuteValue(int id, float value) {}
	float getAttributeValue(int id)const { return 0.0; }
	QList<QPointF> makeMatrix(int width,int height,int count);
};

#endif