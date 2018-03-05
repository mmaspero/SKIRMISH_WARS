#include "buttonToggleSelect.h"

buttonToggleSelect::buttonToggleSelect(button * b) : SkirmishEvent(EV_TOGGLE_SELECT)
{
	this->b = b;
}

buttonToggleSelect::~buttonToggleSelect()
{
}

button * buttonToggleSelect::getButton()
{
	return b;
}
