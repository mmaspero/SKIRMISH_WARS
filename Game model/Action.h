#pragma once
#include "../Point.h"
#include "types.h"

class Action 
{
public:
	Action(action_t type, Point whereTo, unsigned int mps = 0);
	action_t basicType();
	const action_t type;
	unsigned int mps;	//moving points que se gastan por esta accion
	Point whereTo;		//para ataques, posicion desde la que tengo que atacar. para movimientos, posicion final
};