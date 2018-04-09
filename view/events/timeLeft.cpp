#include "timeLeft.h"


timeLeft::timeLeft(unsigned int time) : SkirmishEvent(EV_TIME_LEFT)
{
	this->time = time;
}

timeLeft::~timeLeft()
{
}

unsigned int timeLeft::getTime()
{
	return time;
}
