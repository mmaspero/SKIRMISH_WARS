#include "buttonPress.h"



buttonPress::buttonPress(button * b) : SkirmishEvent(EV_BUTTON_PRESS)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}


buttonPress::~buttonPress()
{
}

button * buttonPress::getButton()
{
	return b;
}
