#include "buttonUnselect.h"

buttonUnselect::buttonUnselect(button * b) : SkirmishEvent(EV_BUTTON_UNSELECT)
{
	this->b = b;
}

buttonUnselect::~buttonUnselect()
{
}

button * buttonUnselect::getButton()
{
	return b;
}
