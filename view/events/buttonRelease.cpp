#include "buttonRelease.h"

buttonRelease::buttonRelease(button * b) : SkirmishEvent(EV_BUTTON_RELEASE)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}

buttonRelease::~buttonRelease()
{
}

button * buttonRelease::getButton()
{
	return b;
}
