#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#include "rhino.h"

class RHINO_EXPORT TimeManager
{
public:
	virtual ~TimeManager() = default;

#define TimeManager_Speed_Slow   1
#define TimeManager_Speed_Normal 2
#define TimeManager_Speed_2X     4
#define TimeManager_Speed_4X     8
	virtual void setSpeed(int speed) = 0;
	virtual int  getSpeed()const = 0;
};

#endif