#include "Apc.h"
#include "../unitInfo.h"
#include "../Attack.h"
#include "../Move.h"
#include <iterator>

Apc::Apc(Point position, bool isMine) : Unit(APC, position, isMine, AP_DEFENSE, 0, 0)
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

int Apc::getTerrainMod(terrain_t t)
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

void Apc::getPossibleUnloads(std::list<Move>* ul)
{
	if (!loadedUnits.empty()) {
		Unit * u = loadedUnits.back();
		std::list<Move> m;
		std::list<Attack> a; //para poder llamar a getPossibleActions
		u->getPossibleActions(&m, &a);
		
		while (!m.empty()) {
			Move move = m.front();
			if (position.orthogonalDistanceFrom(move.whereTo) <= 1) {
				ul->push_back(move);
			}
			m.pop_front();
		}
	}
}



bool Apc::load(Unit * u)
{
	bool valid = false;

	if (loadedUnits.size() < AP_CAPACITY) {
		loadedUnits.push_back(u);
		map->updateUnitPos(u, position, true);	//el true indica que la cargo al apc
		((Apc *)u)->position = position;		//tengo que castear para poder acceder a position
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
		u->move(Move(whereTo, 0));
	}

	return valid;
}
