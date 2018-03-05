#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"

class buttonRelease : public SkirmishEvent
{
public:
	buttonRelease(button * b);
	~buttonRelease();

	button * getButton();

private:
	button * b;
};
