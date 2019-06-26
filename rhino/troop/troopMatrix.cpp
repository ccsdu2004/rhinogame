#include "troopMatrix.h"
#include "troopMatrix_rect.h"
#include "troopMatrix_rect5.h"

TroopMatrix::~TroopMatrix()
{
}

std::shared_ptr<TroopMatrix> TroopMatrix::createTroopMatrix(int type)
{
	switch (type)
	{
	case TroopMatrix_Rect:
		return std::shared_ptr<TroopMatrix>(new TroopMatrix_rect());
	case TroopMatrix_Rect5:
		return std::shared_ptr<TroopMatrix>(new TroopMatrix_rect5());
	default:
		return nullptr;
	}
}