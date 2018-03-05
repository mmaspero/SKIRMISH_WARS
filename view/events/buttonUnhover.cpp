#include "buttonUnhover.h"



buttonUnhover::buttonUnhover(button * b) : SkirmishEvent(EV_HOVER)
{
	this->b = b;	//TODO: no tiene validacion de parametros de entrada
}

buttonUnhover::~buttonUnhover()
{
}
