#include "buttonRelease.h"

buttonRelease::buttonRelease(button * b) : SkirmishEvent(EV_HOVER)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}

buttonRelease::~buttonRelease()
{
}
