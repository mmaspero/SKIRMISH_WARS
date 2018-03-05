#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"

class buttonPress : public SkirmishEvent
{
public:
	buttonPress(button * b);
	~buttonPress();

	button * getButton();

private:
	button * b;
};

