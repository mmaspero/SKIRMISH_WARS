#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"
#include "../button.h"

class buttonUnselect : public SkirmishEvent
{
public:
	buttonUnselect(button * b);
	~buttonUnselect();

	button * getButton();

private:
	button * b;
};
