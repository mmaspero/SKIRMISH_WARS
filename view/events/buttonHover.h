#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"
#include "../button.h"

class buttonHover : public SkirmishEvent
{
public:
	buttonHover(button * b);
	~buttonHover();

	button * getButton();

private:

	button * b;
};