#pragma once
#include "../Unit.h"

class Mech : public Unit {
public:
	Mech(Point position, bool isMine);

	virtual unsigned int restoreMPs();
	virtual int getTerrainMod(terrain_t t);
	virtual unsigned int getAttackMod(unitType_t basicType);	//devuelve el mod, dependiendo de si la unit esta o no reducida
}; 