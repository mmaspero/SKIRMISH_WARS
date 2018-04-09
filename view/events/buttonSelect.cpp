#include "buttonSelect.h"

buttonSelect::buttonSelect(button * b) : SkirmishEvent(EV_BUTTON_SELECT)
{
	this->b = b;
}

buttonSelect::~buttonSelect()
{
}

button * buttonSelect::getButton()
{
	return b;
}
