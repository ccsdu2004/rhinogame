#ifndef TROOP_MATRIX_H
#define TROOP_MATRIX_H
#include <memory>
#include <QPoint>
#include <QList>
#include "rhino.h"

class RHINO_EXPORT TroopMatrix
{
public:
#define TroopMatrix_Rect  0
#define TroopMatrix_Rect5 1
	static std::shared_ptr<TroopMatrix> createTroopMatrix(int type);

	virtual ~TroopMatrix();

	virtual void setAttirbuteValue(int id,float value) = 0;
	virtual float getAttributeValue(int id)const = 0;
	virtual QList<QPointF> makeMatrix(int width,int height,int count) = 0;
};

#endif