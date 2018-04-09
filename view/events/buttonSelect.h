#pragma once

#include "../../Game model/FSM/SkirmishEvent.h"
#include "../button.h"

class buttonSelect : public SkirmishEvent
{
public:
	buttonSelect(button * b);
	~buttonSelect();

	button * getButton();

private:

	button * b;
};
