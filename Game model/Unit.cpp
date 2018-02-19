#include "Unit.h"
#include "Action.h"
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
#include <cstdint>

Map * Unit::map = nullptr;
std::unordered_map<unit_t, Unit *> Unit::info;

#define CANT_REACH	-1

unsigned int getDamage(int initDamage, terrain_t t, building_t b, unsigned int diceRoll);



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

basicUnitType_t Unit::getBasicType()
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

unsigned int Unit::getAttackMod(unit_t type, basicUnitType_t basicType)
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

bool Unit::heal()
{
	bool hpsChanged = false;
	if (isAlive()) { //no curo unidades muertas!
		
		healthPoints += HEAL_HP;

		if (healthPoints > MAX_HP)
			healthPoints = MAX_HP;

		if (type == APC) {
			hpsChanged |= ((Apc *)this)->healLoadedUnits();
		}

		if (hpsChanged == true) {
			map->notifyTileObserver(position);
		}
	}

	return hpsChanged;
}

void Unit::endTurn()
{
	if (state != IDLE) {
		state = POST_ACTIVE;
	}
}

void Unit::nextTurn()
{
	state = IDLE;
	restoreMPs();
}

int Unit::isActionValid(Action act)
{
	int mps = CANT_REACH;

	std::list<Action> actList;
	getPossibleActions(actList);

	for (std::list<Action>::iterator it = actList.begin(); it != actList.end() && mps == CANT_REACH; it++) {
		if (it->whereTo == act.whereTo && it->basicType() == act.basicType()) {
			mps = it->mps;
		}
	}

	return mps;
}

bool Unit::move(Action mov)
{
	bool valid = false;

	if (mov.type == ACT_MOVE && mov.mps == isActionValid(mov) && map->updateUnitPos(this, mov.whereTo)) {
		position = mov.whereTo;
		movingPoints -= mov.mps;
		state = MOVING; // la unica accion que no prohibe mas movs es MOVE
		valid = true;
	}
	
	return valid;
}

bool Unit::attack(Action att, unsigned int diceRoll)
{
	bool valid = false;
	if (att.type == ACT_ATTACK && att.mps == isActionValid(att) && 1 <= diceRoll && diceRoll <= 6) {
		valid = true;
		Unit * enemy = map->getUnit(att.whereTo);
		terrain_t t = map->getTerrain(att.whereTo);
		building_t b = map->hasBuilding(att.whereTo) ? map->getBuilding(att.whereTo)->getType() : N_BUILDINGS;
		int initDamage = getAttackMod(enemy->getBasicType()) - enemy->defense; //aca ya se tiene en cuenta si esta reducido o no

		enemy->healthPoints -= getDamage(initDamage, t, b, diceRoll);

		if (enemy->healthPoints < 0) {
			enemy->healthPoints = 0;
		}

		state = ATTACKING;
		map->notifyTileObserver(att.whereTo);
	}
	return valid;
}

bool Unit::startCapture(Action capt)
{
	bool valid = false; 

	if (capt.type == ACT_CAPTURE && isActionValid(capt) != CANT_REACH && map->updateUnitPos(this, capt.whereTo)) {
		position = capt.whereTo;
		movingPoints -= capt.mps;
		state = POST_ACTIVE; //despues de una captura no puedo moverme mas! es como un ataque
		valid = true;
	}

	return valid;
}

void Unit::getPossibleActions(std::list<Action>& actions)
{
	if (map == nullptr)
		return;

	if (state <= MOVING) {
		getPossibleMoves(actions, position, position, movingPoints);
	}

	if (state == IDLE || (state == MOVING && maxRange == 1)) {
		getPossibleAttacks(actions, position); 
	}

	if (state == UNLOADING) {
		((Apc *)this)->getPossibleUnloads(actions);
	}		
}

void Unit::getPossibleMoves(std::list<Action>& moves, Point start, Point curr, unsigned int mps)
{
	if (map == nullptr || !map->isInMap(curr))
		return;

	unsigned int mod = UINT_MAX;
	action_t actionType = N_ACTIONS; //si esto queda asi es que no hay ninguna accion valida

	if (start != curr) { // me fijo si puedo venir a esta casilla, y cuanto me cuesta

		if (!map->hasFog(curr, getPlayer())) { //solo puedo ir a casillas que puedo ver
			
			if (getBasicType() == FOOT) {
				if (map->canBoard(curr, getPlayer())) { //solo puedo ir a donde hay una unit si es un apc de los mios
					actionType = ACT_LOAD; //solo si tiene un apc mio y soy foot
				}
				else if (map->canCapture(curr, getPlayer())) {
					actionType = ACT_CAPTURE; //los foot pueden capturar edificios enemigos
				}
			}
			
			if (!map->hasUnit(curr) && actionType == N_ACTIONS) { //los movimientos son a lugares sin unidades!
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
		if (start != curr && (actionType < N_ACTIONS)) { //no calculo camino optimo si la distancia es 0

			for (std::list<Action>::iterator it = moves.begin(); it != moves.end() && newTile == true; it++) {
				if (it->whereTo == curr) {
					newTile = false;	// tile repetida!

					if (it->mps > action.mps) {	//si el camino es mas corto, lo actualizo
						it->mps = action.mps;	//(en it estan los que cuestan, movingPoints son los que tiene la unidad
					}									//y mps los que todavia me quedan para gastar de esos)
				}
			}
		}

		if (newTile == true && actionType != N_ACTIONS) { //solo añado un item a la lista si es una tile nueva
			moves.push_back(action);
		}

		if (action.type != ACT_LOAD) {
			//veo a que tiles puedo ir desde aca
			curr.row -= 1;				// abajo
			getPossibleMoves(moves, start, curr, mps);

			curr.row += 2;				// arriba
			getPossibleMoves(moves, start, curr, mps);

			curr.row -= 1; curr.col -= 1;	//izquierda
			getPossibleMoves(moves, start, curr, mps);

			curr.col += 2;				//derecha
			getPossibleMoves(moves, start, curr, mps);
		}
	}
}

void Unit::getPossibleAttacks(std::list<Action>& attacks, Point curr)
{
	if (map == nullptr)
		return;

	//voy a recorrer todo el mapa y fijarme cuales unidades enemigas estan dentro de mi rango
	for (unsigned int i = 0; i<B_H; i++) {
		for (unsigned int j = 0; j<B_W; j++) {
			Point p(i, j);
			unsigned int dist = curr.orthogonalDistanceFrom(p); 

			if (minRange <= dist && dist <= maxRange && map->hasUnit(p)
				&& (isMine ^ (map->getUnitPlayer(p) == USER)) && map->canSeeUnit(p, getPlayer())) {
				//me fijo si esta casilla la puedo atacar con menos MPs desde otro lugar o no
				attacks.push_back(Action(ACT_ATTACK, p));
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
	std::list<Action> act;
	getPossibleActions(act);

	return act.size();
}


#define MIN_DAMAGE	-3
#define MAX_DAMAGE	13
typedef struct {
	uint8_t damage;			
	uint8_t maxDice;		//si saco esto o menos, hago un punto mas de danio
}  terrainDefenseMod_t;

unsigned int getDamage(int initDamage, terrain_t t, building_t b, unsigned int diceRoll)
{
	unsigned int ans = UINT_MAX;

	if (MIN_DAMAGE <= initDamage && initDamage <= MAX_DAMAGE && 1 <= diceRoll && diceRoll <= 6 && t <= N_TERRAINS) {
		terrainDefenseMod_t defMods[MAX_DAMAGE - MIN_DAMAGE + 1][N_TERRAINS] = {
			//GRASS		BUILDING	RIVER/ROAD	FOREST	HILL/HQ
			{ {0, 0},	{0, 0},		{0, 1},		{0, 0},  {0, 0} },	//-3 (MIN_DAMAGE)
			{ {0, 1},	{0, 0},		{0, 2},		{0, 1},  {0, 0} },	//-2
			{ {0, 2},	{0, 1},		{0, 3},		{0, 2},  {0, 1} },	//-1
			{ {0, 4},	{0, 2},		{0, 5},		{0, 3},  {0, 1} },	//0
			{ {1, 2},	{1, 1},		{1, 3},		{1, 1},  {0, 5} },	//1
			{ {2, 2},	{1, 5},		{2, 3},		{2, 1},  {1, 3} },	//2
			{ {3, 1},	{2, 3},		{3, 3},		{2, 5},  {2, 1} },	//3
			{ {4, 1},	{3, 1},		{4, 3},		{3, 4},  {2, 4} },	//4
			{ {4, 5},	{3, 5},		{5, 3},		{4, 2},  {3, 2} },	//5
			{ {5, 5},	{4, 3},		{6, 3},		{5, 1},  {3, 5} },	//6
			{ {6, 5},	{5, 1},		{7, 3},		{6, 1},  {4, 3} },	//7
			{ {7, 4},	{5, 5},		{8, 0},		{6, 5},  {5, 1} },	//8
			{ {8, 0},	{6, 4},		{8, 0},		{7, 4},  {5, 4} },	//9
			{ {8, 0},	{7, 2},		{8, 0},		{8, 0},  {6, 2} },	//10
			{ {8, 0},	{8, 0},		{8, 0},		{8, 0},  {6, 5} },	//11
			{ {8, 0},	{8, 0},		{8, 0},		{8, 0},  {7, 3} },	//12
			{ {8, 0},	{8, 0},		{8, 0},		{8, 0},  {8, 0} },	//13 (MAX_DAMAGE)
		};

		if (t == ROAD) {
			t = RIVER;	//TIENEN LOS MISMOS MODIFICADORES
		}
		else if (b == HEADQUARTERS) {
			t = HILL;	
		}
		else if (b < N_BUILDINGS) {
			t = ROAD; //USO EL LUGAR DE ROAD EN EL ENUM PORQUE SOBRA
		}

		initDamage -= MIN_DAMAGE;	//lo llevo a zero-based

		ans = defMods[initDamage][t].damage;
		if (diceRoll <= defMods[initDamage][t].maxDice) {
			ans++;
		}
	}

	return ans;
}
