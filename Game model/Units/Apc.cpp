#include "Apc.h"
#include "../unitInfo.h"
#include "../Attack.h"
#include "../Action.h"
#include <iterator>

Apc::Apc(Point position, bool isMine) : Unit(APC, position, isMine, AP_COST, AP_DEFENSE, 0, 0)
{
	restoreMPs();
}

Apc::~Apc()
{
	while (!loadedUnits.empty()) {
		delete loadedUnits.front();
		loadedUnits.pop_front();
	}
}

unsigned int Apc::restoreMPs()
{
	movingPoints = AP_MP;
	for (std::list<Unit *>::iterator it = loadedUnits.begin(); it != loadedUnits.end(); it++) {
		(*it)->restoreMPs();
	}

	return movingPoints;
}

unsigned int Apc::getTerrainMod(terrain_t t)
{
	switch (t) {
	case GRASS:
		return AP_MC_T;
	case RIVER:
		return AP_MC_R;
	case ROAD:
		return AP_MC_A;
	case FOREST:
		return AP_MC_F;
	case HILL:
		return AP_MC_H;

	default:
		return UINT_MAX;
	}
}

unsigned int Apc::getAttackMod(unitType_t basicType)
{	
	return UINT_MAX;
}

bool Apc::canBoard(bool player)
{
	if (loadedUnits.size() < AP_CAPACITY && isMine == player)
		return true;
	else
		return false;
}

unsigned int Apc::nLoadedUnits()
{
	return loadedUnits.size();
}

void Apc::healLoadedUnits()
{
	for (std::list<Unit *>::iterator it = loadedUnits.begin(); it != loadedUnits.end(); it++) {
		(*it)->heal();
	}
}

void Apc::getPossibleUnloads(std::list<Action *>& ul)
{
	if (!loadedUnits.empty()) {
		Unit * u = loadedUnits.back();
		std::list<Action *> a;
		u->getPossibleActions(a);
		
		while (!a.empty()) {
			Action * action = a.front();
			if (action->type != ACT_ATTACK && position.orthogonalDistanceFrom(action->whereTo) <= 1) {
				Action * unload = new Action(ACT_UNLOAD, action->whereTo, action->mps);
				ul.push_back(action);
			}
			delete action;
			a.pop_front();
		}
	}
}



bool Apc::load(Unit * u)
{
	bool valid = false;

	if (loadedUnits.size() < AP_CAPACITY) {
		loadedUnits.push_back(u);
		valid = true;
	}

	return valid;
}

bool Apc::unload(Point whereTo)
{
	bool valid = false;
	if (loadedUnits.size() != 0 && position.orthogonalDistanceFrom(whereTo) == 1) {
		Unit * u = loadedUnits.back();
		loadedUnits.pop_back();
		u->move(Action(ACT_MOVE, whereTo, 0));
	}

	return valid;
}
