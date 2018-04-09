#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"
#include "../button.h"

class timeLeft : public SkirmishEvent
{
public:
	timeLeft(unsigned int time);
	~timeLeft();

	unsigned int getTime();

private:
	unsigned int time;
};
