#include "myTimer.h"
#include <time.h>


myTimer::myTimer(unsigned int miliseconds)
{
	this->miliseconds=miliseconds;
	resetTime();
}

myTimer::~myTimer()
{
}

void myTimer::setNewTime(unsigned int miliseconds)
{
	this->miliseconds = miliseconds;
	resetTime();
}

void myTimer::resetTime()
{
	finalTime = (clock() + ((CLOCKS_PER_SEC*miliseconds )/ 1000.0));
}

bool myTimer::timeOut()
{
	if (clock() > finalTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int myTimer::restTime()
{
	return ((((float)(clock() - finalTime)) / CLOCKS_PER_SEC)*1000.0);
}
