#ifndef TIME_MANAGER_PRIV_H
#define TIME_MANAGER_PRIV_H
#include "timeManager.h"

class TimeManagerPriv : public TimeManager
{
public:
	TimeManagerPriv();
	~TimeManagerPriv();
public:
	void setSpeed(int speed);
	int  getSpeed()const;
private:
	int timeSpeed;
};


#endif