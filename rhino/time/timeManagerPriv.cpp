#include "timeManagerPriv.h"
#include "world.h"

#define TIME_VALUE 24

TimeManagerPriv::TimeManagerPriv():
timeSpeed(TimeManager_Speed_Normal)
{
}

TimeManagerPriv::~TimeManagerPriv()
{
}

void TimeManagerPriv::setSpeed(int speed)
{
	timeSpeed = speed;
}

int TimeManagerPriv::getSpeed()const
{
	return timeSpeed;
}