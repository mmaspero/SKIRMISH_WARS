#pragma once
#include "../Unit.h"

class AntiAir : public Unit {
public:
	AntiAir(Point position, bool isMine);

	virtual unsigned int restoreMPs();
	virtual int getTerrainMod(terrain_t t);
	virtual unsigned int getAttackMod(unitType_t basicType);	//devuelve el mod, dependiendo de si la unit esta o no reducida
}; 