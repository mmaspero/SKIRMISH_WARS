#include "Unit.h"
#include "Units\AntiAir.h"
#include "Units\Apc.h"
#include "Units\Artillery.h"
#include "Units\Infantry.h"
#include "Units\Mech.h"
#include "Units\MedTank.h"
#include "Units\Recon.h"
#include "Units\Rocket.h"
#include "Units\Tank.h"
#include <iterator>

Map * Unit::map = nullptr;
std::unordered_map<unit_t, Unit *> Unit::info;

#define CANT_REACH	-1

unsigned int getDamage(int initDamage, terrain_t t, unsigned int diceRoll);



Unit::Unit(unit_t type, Point position, bool isMine, unsigned int cost, unsigned int defense, unsigned int minRange,
	unsigned int maxRange) : cost(cost), type(type), isMine(isMine), defense(defense), minRange(minRange), maxRange(maxRange)
{
	bool valid = false;
	if (type >= 0 && type < N_UNIT_TYPES && Map::isInMap(position)) { //solo puedo verificar si el punto se fue de rango si ya tengo el mapa
		this->position = position;
		valid = true;
		healthPoints = MAX_HP;
		state = IDLE;
	}
	
	if (!valid) {
		this->position.row = B_W;
		this->position.col = B_H;
		state = N_UNIT_STATES; //para indicar que esta unidad no se puede usar
	}
}

Unit::~Unit()
{
	;
}

unit_t Unit::getType()
{
	return type;
}

unitType_t Unit::getBasicType()
{
	if (FIRST_W <= type && type < FIRST_F)
		return WHEEL;

	else if (FIRST_F <= type && type < FIRST_T)
		return FOOT;

	else if (FIRST_T <= type && type < N_UNIT_TYPES)
		return TREAD;

	else
		return N_BASIC_U_TYPES;
}

unsigned int Unit::getCost()
{
	return cost;
}

Unit * Unit::factory(unit_t type, Point p, bool isMine)
{
	Unit * u = nullptr;

	switch (type) {
	case RECON:		{ u = new Recon(p, isMine); }		break;
	case ROCKET:	{ u = new Rocket(p, isMine); }		break;
	case MECH:		{ u = new Mech(p, isMine); }		break;
	case INFANTRY:	{ u = new Infantry(p, isMine); }	break;
	case TANK:		{ u = new Tank(p, isMine); }		break;
	case ARTILLERY: { u = new Artillery(p, isMine); }	break;
	case ANTIAIR:	{ u = new AntiAir(p, isMine); }		break;
	case APC:		{ u = new Apc(p, isMine); }			break;
	case MEDTANK:	{ u = new MedTank(p, isMine); }		break;
		//cualquier otro caso queda en nullptr como corresponde
	}
	
	return u;
}

void Unit::init(Map * map)
{
	if (Unit::map == nullptr && map != nullptr) {
		Unit::map = map;
		Point p(B_H, B_W);
		info.emplace(RECON, new Recon(p, true));
		info.emplace(ROCKET, new Rocket(p, true));
		info.emplace(MECH, new Mech(p, true));
		info.emplace(INFANTRY, new Infantry(p, true));
		info.emplace(TANK, new Tank(p, true));
		info.emplace(ARTILLERY, new Artillery(p, true));
		info.emplace(ANTIAIR, new AntiAir(p, true));
		info.emplace(APC, new Apc(p, true));
		info.emplace(MEDTANK, new MedTank(p, true));
	}
}

void Unit::end()
{
	map = nullptr;

	for (std::unordered_map<unit_t, Unit *>::iterator it = info.begin(); it != info.end(); it++) {
		delete it->second;
	}

	info.clear();
}

unsigned int Unit::getCost(unit_t type)
{
	unsigned int cost = UINT_MAX;

	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		cost = it->second->getCost();
	}

	return cost;
}

unsigned int Unit::getTerrainMod(unit_t type, terrain_t t)
{
	unsigned int ans = UINT_MAX;

	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		ans = it->second->getTerrainMod(t);
	}

	return ans;
}

unsigned int Unit::getAttackMod(unit_t type, unitType_t basicType)
{
	unsigned int ans = UINT_MAX;

	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		ans = it->second->getAttackMod(basicType);
	}

	return ans;
}

void Unit::getRange(unit_t type, unsigned int& minRange, unsigned int& maxRange)
{
	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		minRange = it->second->minRange;
		maxRange = it->second->maxRange;
	}
	else {
		minRange = UINT_MAX;
		maxRange = UINT_MAX;
	}
}

unsigned int Unit::getDefense(unit_t type)
{
	unsigned int ans = UINT_MAX;

	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		ans = it->second->defense;
	}

	return ans;
}

unsigned int Unit::getMaxMps(unit_t type)
{
	unsigned int ans = UINT_MAX;

	std::unordered_map<unit_t, Unit *>::const_iterator it = info.find(type);
	if (it != info.end()) {
		ans = it->second->defense;
	}

	return ans;
}

bool Unit::isAlive()
{
	return (healthPoints > 0 && state != N_UNIT_STATES);
}

player_t Unit::getPlayer()
{
	return (isMine? USER : OPPONENT);
}

Point Unit::getPosition()
{
	return position;
}

void Unit::heal()
{
	if (isAlive()) { //no curo unidades muertas!
		healthPoints += HEAL_HP;

		if (healthPoints > MAX_HP)
			healthPoints = MAX_HP;

		if (type == APC) {
			((Apc *)this)->healLoadedUnits();
		}
	}
}

bool Unit::isActionValid(Action * act)
{
	bool ans = false;

	if (act != nullptr) {
		std::list<Action *> actList;
		getPossibleActions(actList);

		while (actList.size()) {
			Action * it = actList.front();
			
			if (it->whereTo == act->whereTo && it->type == act->type) {
				if (it->type == ACT_ATTACK) {
					if (((Attack *)it)->target == ((Attack *)act)->target) {
						ans = true;
					}
				}
				else {
					ans = true;
				}
			}

			delete it;
		}
	}

	return ans;
}

bool Unit::move(Action a)
{
	if (map != nullptr && !map->isInMap(a.whereTo) || a.mps > movingPoints || !isAlive()
		|| !map->updateUnitPos(this, a.whereTo, a.type == ACT_LOAD))
		return false;
	
	position = a.whereTo;
	movingPoints -= a.mps;
	return true;
}

int Unit::attack(Attack a, unsigned int diceRoll)
{
	if (map != nullptr && !map->isInMap(a.target) || !map->hasUnit(a.target) || 
		!isAlive() || !(isMine ^ (map->getPlayer(a.target) == USER)) ||!move(a) )
		return false;

	Unit * enemy = map->getUnit(a.target);
	terrain_t t = map->getTerrain(a.target);
	int initDamage = getAttackMod(enemy->getBasicType()) - enemy->defense; //aca ya se tiene en cuenta si esta reducido o no
	
	enemy->healthPoints -= getDamage(initDamage, t, diceRoll);

	return true;
}

void Unit::getPossibleActions(std::list<Action *>& actions)
{
	if (state >= ATTACKING || map == nullptr)
		return;				//despues de atacar no puedo hacer nada

	std::list<Action *> attacks;
	bool newAttacks[B_H * B_W];	//para saber que casillas ya tienen registrado un ataque
	memset(newAttacks, 0, sizeof(bool)*B_H*B_W);	// pongo todo en false: todavia no ataque nada

	if (state <= MOVING) {
		getPossibleMoves(actions, position, position, movingPoints);
	}

	if (state == IDLE) {
		getPossibleAttacks(newAttacks, attacks, position); //estos ataques cuestan 0 mps (por defecto)
	}

	if (state == MOVING && maxRange == 1) { //los de rango 1 pueden atacar despues de moverse
		for (std::list<Action *>::iterator it = actions.begin(); it != actions.end(); it++) {
			if ((*it)->type == ACT_MOVE) { // me fijo de no atacar desde un APC
				getPossibleAttacks(newAttacks, attacks, (*it)->whereTo, (*it)->mps);
				// estos cuentan tantos mps como moverse a la casilla desde donde se hacen
			}
		}
	}
	
	if (state == UNLOADING) {
		((Apc *)this)->getPossibleUnloads(actions);
	}
		
}

void Unit::getPossibleMoves(std::list<Action *>& moves, Point start, Point curr, unsigned int mps)
{
	if (map == nullptr || !map->isInMap(curr))
		return;

	unsigned int mod = UINT_MAX;
	action_t actionType = N_ACTIONS; //si esto queda asi es que no hay ninguna accion valida

	if (start != curr) { // me fijo si puedo venir a esta casilla, y cuanto me cuesta

		if (!map->hasFog(curr, getPlayer())) { //solo puedo ir a casillas que puedo ver
			if (map->hasUnit(curr)) {
				if ((getBasicType() == FOOT && map->getUnit(curr)->type == APC
					&& ((Apc *)(map->getUnit(curr)))->canBoard(isMine))) { 
					actionType = ACT_LOAD; //solo si tiene un apc mio y soy foot
				}
			}
			else {
				actionType = ACT_MOVE; //si no tiene unidad y la puedo ver puede ser un move
			}
		}

		if (actionType != N_ACTIONS) {
			mod = getTerrainMod(map->getTerrain(curr));
		}

	}
	else {
		mod = 0;	//no necesito mps para moverme a la casilla donde estoy (para que no haya errores en la primera llamada)

		if (type == APC && ((Apc *)this)->nLoadedUnits() != 0) {
			actionType = ACT_UNLOAD; //si soy un apc mi misma casilla es unload
		}
	}


	if (mod <= mps) { //puedo moverme a esta casilla
		mps -= mod; //a los mps que me quedan les tengo que restar lo que cuesta este ultimo paso
		Action action(actionType, curr, movingPoints - mps);
		//mps que cuesta esta accion: los que tiene la unidad, menos los que me quedan

		bool newTile = true;	//para saber si ya habia un camino a esta tile o no
		if (start != curr && (actionType == ACT_LOAD || actionType == ACT_MOVE)) { //no calculo camino optimo si la distancia es 0

			for (std::list<Action *>::iterator it = moves.begin(); it != moves.end() && newTile == true; it++) {
				if ((*it)->whereTo == curr) {
					newTile = false;	// tile repetida!

					if ((*it)->mps > action.mps) {	//si el camino es mas corto, lo actualizo
						(*it)->mps = action.mps;	//(en it estan los que cuestan, movingPoints son los que tiene la unidad
					}									//y mps los que todavia me quedan para gastar de esos)
				}
			}
		}

		if (newTile == true && actionType != N_ACTIONS) { //solo añado un item a la lista si es una tile nueva
			moves.push_back(new Action(action));
		}

		if (action.type != ACT_LOAD) {
			//veo a que tiles puedo ir desde aca
			curr.row -= 1;				// a la izquierda
			getPossibleMoves(moves, start, curr, mps);

			curr.row += 2;				//a la derecha
			getPossibleMoves(moves, start, curr, mps);

			curr.row -= 1; curr.col -= 1;	//arriba
			getPossibleMoves(moves, start, curr, mps);

			curr.col += 2;				//abajo
			getPossibleMoves(moves, start, curr, mps);
		}
	}
}

void Unit::getPossibleAttacks(bool * newAttacks, std::list<Action *>& attacks, Point curr, unsigned int movingPoints)
{
	if (map == nullptr)
		return;

	//voy a recorrer todo el mapa y fijarme cuales unidades enemigas estan dentro de mi rango
	for (unsigned int i = 0; i<B_H; i++) {
		for (unsigned int j = 0; j<B_W; j++) {
			Point p(i, j);
			unsigned int dist = curr.orthogonalDistanceFrom(p); 

			if (minRange <= dist && dist <= maxRange && map->hasUnit(p)
				&& (isMine ^ (map->getPlayer(p) == USER)) && !map->hasFog(p, getPlayer())) {
				//me fijo si esta casilla la puedo atacar con menos MPs desde otro lugar o no

				if (newAttacks[i*B_W + j] == true) { 
					newAttacks[i*B_W + j] = false; //el ataque ya existe: me fijo si puedo mejorar los MPs
					for (std::list<Action *>::iterator it = attacks.begin(); it != attacks.end() && newAttacks[i*B_W + j] == false; it++) {
						if ((*it)->whereTo == curr) {
							newAttacks[i*B_W + j] = true;
							if (movingPoints < (*it)->mps) {
								(*it)->mps = movingPoints;
							}
						}
					}
				}
				else {
					attacks.push_back(new Attack(p, curr, movingPoints));
					newAttacks[i*B_W + j] = true; // ataque nuevo
				}
			}
		}
	}
}

bool Unit::isReduced()
{
	if (healthPoints <= REDUCED_HP && healthPoints > 0)
		return true;
	else
		return false;
}

bool Unit::hasValidActions()
{
	bool ans = false;
	std::list<Action *> act;
	getPossibleActions(act);

	if (act.size()) {
		ans = true;
		
		while (act.size()) {
			delete act.front();
			act.pop_front();
		}
	}

	return ans;
}

unsigned int getDamage(int initDamage, terrain_t t, unsigned int diceRoll)
{
	return rand()%3; //we. obviamente esto no es asi
}
