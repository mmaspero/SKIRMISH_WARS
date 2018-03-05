#pragma once

#include "..\button.h"
#include "../../Game model/FSM/SkirmishEvent.h"

class buttonToggleSelect : public SkirmishEvent
{
public:
	buttonToggleSelect(button * b);
	~buttonToggleSelect();

	button * getButton();

private:
	button * b;

};
