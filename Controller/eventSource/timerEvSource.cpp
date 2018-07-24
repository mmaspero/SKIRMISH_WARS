#include "timerEvSource.h"
#include "../../Game model/FSM/FsmInfo.h"
timerEvSource::timerEvSource(unsigned int seconds)
{
	this->secondsSet = seconds;
	this->timerStart = false;
}

timerEvSource::~timerEvSource()
{
}

GenericEvent * timerEvSource::getEvent()
{
	if ((clock() > (this->tInicial)) && timerStart)
	{
		stopTimer();
		return new GenericEvent(EV_TIMEOUT);
	}
	return NULL;
}

void timerEvSource::setTime(unsigned int seconds)
{
	this->secondsSet = seconds;
}

void timerEvSource::startTimer()
{
	this->timerStart = true;
	this->resetTimer();
}

void timerEvSource::stopTimer()
{
	this->timerStart = false;
}

void timerEvSource::resetTimer()
{
	this->tInicial = clock() + ((this->secondsSet)*CLOCKS_PER_SEC);

}

unsigned int timerEvSource::getRestTimer()
{
	unsigned int restTime = 0;
	if (clock() < (this->tInicial))
	{
		restTime = ((this->tInicial) - clock())/ CLOCKS_PER_SEC;
	}
	return restTime;
}
