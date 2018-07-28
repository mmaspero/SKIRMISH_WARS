#include "timerEvSource.h"
#include "../../Game model/FSM/FsmInfo.h"
#include "../../view/events/timeLeft.h"
#include <iostream>
timerEvSource::timerEvSource(unsigned int seconds)
{
	this->secondsSet = seconds;
	this->timerStart = false;
	offClock();
}

timerEvSource::~timerEvSource()
{
}

GenericEvent * timerEvSource::getEvent()
{
	unsigned int restTime = 0;
	if ((clock() >= (this->tInicial)) && timerStart)
	{
		stopTimer();
		//std::cout << "TIME OUT" << std::endl;
		return new GenericEvent(EV_TIMEOUT);
	}

	restTime = getRestTimer()+1;
	if (restTime<=secondsSetClock && this->enableClock)
	{
	
		if (restTime > sampleTimeSec)
		{
			this->secondsSetClock = restTime - sampleTimeSec;
		}
		else
		{
			this->secondsSetClock = 0;
		}
		//std::cout << "tiempo con el que se llama al evento: " << restTime << std::endl;
		return new timeLeft(restTime);


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
	timerStart = true;
	this->tInicial = clock() + ((this->secondsSet)*CLOCKS_PER_SEC);
	if (enableClock)
	{
		onClock(this->sampleTimeSec);
	}

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

void timerEvSource::onClock(unsigned int sampleTimeSec)
{
	enableClock = true;
	unsigned int restTime = getRestTimer()+1;
	this->sampleTimeSec = sampleTimeSec;
	if (restTime > sampleTimeSec)
	{
		this->secondsSetClock = restTime - sampleTimeSec;
	}
	else
	{
		this->secondsSetClock = 0;
	}
	

}

void timerEvSource::offClock()
{
	enableClock = false;
}
