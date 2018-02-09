#pragma once
#include "../Unit.h"

class Recon : public Unit {
public:
	Recon(Point position, bool isMine);

	virtual unsigned int restoreMPs();
	virtual unsigned int getTerrainMod(terrain_t t);
	virtual unsigned int getAttackMod(basicUnitType_t basicType);	//devuelve el mod, dependiendo de si la unit esta o no reducida
};