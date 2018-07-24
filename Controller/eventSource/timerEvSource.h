#pragma once
#include "eventSource.h"
#include <ctime>
class timerEvSource:public eventSource
{
public:
	timerEvSource(unsigned int seconds=0);
	~timerEvSource();
	GenericEvent * getEvent();
	void setTime(unsigned int seconds);
	void startTimer();
	void stopTimer();
	void resetTimer();
	unsigned int getRestTimer();


private:
	clock_t tInicial;
	unsigned int secondsSet;
	bool timerStart;

};
