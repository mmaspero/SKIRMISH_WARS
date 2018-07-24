#include "Apc.h"
#include "../unitInfo.h"
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

void Apc::nextTurn()
{
	state = IDLE;
	restoreMPs();
	for (std::list<Unit *>::iterator it = loadedUnits.begin(); it != loadedUnits.end(); it++) {
		(*it)->nextTurn();
	}

}

unsigned int Apc::restoreMPs()
{
	movingPoints = AP_MP;
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

unsigned int Apc::getAttackMod(basicUnitType_t basicType, bool reduced)
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

unsigned int Apc::canUnload()
{
	std::list<Action> ul;
	getPossibleUnloads(ul);
	return ul.size();
}

bool Apc::healLoadedUnits()
{
	bool hpsUpdated = false;
	for (std::list<Unit *>::iterator it = loadedUnits.begin(); it != loadedUnits.end(); it++) {
		hpsUpdated |= (*it)->heal();
	}
	return hpsUpdated;
}

bool Apc::startUnloading()
{
	bool valid = false;

	if (state <= UNLOADING && loadedUnits.size()) {
		valid = true;
		state = UNLOADING;
	}

	return valid;
}

void Apc::getPossibleUnloads(std::list<Action>& ul)
{
	if (!loadedUnits.empty()) {
		Unit * u = loadedUnits.back();
		u->updatePosition(position);
		std::list<Action> a;
		u->getPossibleActions(a);
		
		while (!a.empty()) {
			Action action = a.front();
			if (action.type != ACT_ATTACK && position.orthogonalDistanceFrom(action.whereTo) <= 1) {
				ul.push_back(Action(ACT_UNLOAD, action.whereTo, action.mps));
			}
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
		u->move(Action(ACT_UNLOAD, whereTo, 0));
		valid = true;
	}
	state = MOVING;
	movingPoints = 0; //el apc no se puede mover despues de descargar!
	return valid;
}
