#include "buttonHover.h"


buttonHover::buttonHover(button * b) : SkirmishEvent(EV_HOVER)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}


buttonHover::~buttonHover()
{
}

button * buttonHover::getButton()
{
	return nullptr;
}
