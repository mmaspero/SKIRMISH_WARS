#include "buttonUnhover.h"



buttonUnhover::buttonUnhover(button * b) : SkirmishEvent(EV_BUTTON_UNHOVER)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}

buttonUnhover::~buttonUnhover()
{
}

button * buttonUnhover::getButton()
{
	return b;
}
