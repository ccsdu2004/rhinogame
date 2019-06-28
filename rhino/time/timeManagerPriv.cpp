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
	if(speed < 0 || speed > TimeManager_Speed_4X)
		return;
	timeSpeed = speed;
}

int TimeManagerPriv::getSpeed()const
{
	return timeSpeed;
}