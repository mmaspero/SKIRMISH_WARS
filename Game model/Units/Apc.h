#pragma once
#include "../Unit.h"
#include <list>

class Apc : public Unit {
public:
	Apc(Point position, bool isMine);
	~Apc();

	virtual unsigned int restoreMPs();
	virtual unsigned int getTerrainMod(terrain_t t);
	virtual unsigned int getAttackMod(unitType_t basicType);	//devuelve el mod, dependiendo de si la unit esta o no reducida

	bool canBoard(bool player);
	unsigned int nLoadedUnits();
	void healLoadedUnits();

	void getPossibleUnloads(std::list<Action *>& ul);

	bool load(Unit * u);		
	bool unload(Point whereTo);		//descarga siempre en orden inverso a como cargo

private:
	std::list<Unit *> loadedUnits;
};