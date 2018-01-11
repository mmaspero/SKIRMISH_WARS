#pragma once
#include "../Point.h"

class Move 
{
public:
	Move(Point target, unsigned int mps = 0);

	unsigned int mps;	//moving points que se gastan por esta accion
	Point whereTo;		//para ataques, posicion del enemigo. para movimientos, posicion final
};