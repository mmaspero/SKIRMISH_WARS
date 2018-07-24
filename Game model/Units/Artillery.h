#pragma once
#include "../Unit.h"

class Artillery : public Unit {
public:
	Artillery(Point position, bool isMine);

	virtual unsigned int restoreMPs();
	virtual unsigned int getTerrainMod(terrain_t t);
	virtual unsigned int getAttackMod(basicUnitType_t basicType, bool reduced);	//devuelve el mod, dependiendo de si la unit esta o no reducida
}; 