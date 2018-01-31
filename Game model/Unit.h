#pragma once
#include "unitInfo.h"
#include "types.h"
#include "Attack.h"
#include "Map.h"
#include <list>
#include <unordered_map>

typedef enum unitStates { IDLE, MOVING, ATTACKING, UNLOADING, POST_ACTIVE, N_UNIT_STATES } unitState_t;
//idle: todavia no se movio
//moving: se movio al menos una vez, puede que haya mas movimientos validos. ya esta activa
//attacking: ya ataco, esta esperando el contra-ataque

class Map;
class Tile;

class Unit	
{
public:
	Unit(unit_t type, Point position, bool isMine, unsigned int cost,
		unsigned int defense, unsigned int minRange, unsigned int maxRange);		
	virtual ~Unit();

	static Unit * factory(unit_t type, Point position, bool isMine);

	static void init(Map * map);	//antes de esta no se puede llamar ninguna estatica ni usar las unidades que crees!!
	static void end();				

	//	INFO GENERAL DE CADA TIPO DE UNIDAD
	//	devuelven UINT_MAX si hubo error o si no esta definido (p. ej, el terrainMod de ciertas unidades para el agua es UINT_MAX
	//porque no pueden ir al agua, o los APCs devuelven UINT_MAX para attackMod porque no pueden atacar)
	static unsigned int getCost(unit_t type);
	static unsigned int getTerrainMod(unit_t type, terrain_t t);
	static unsigned int getAttackMod(unit_t type, unitType_t basicType);
	static void getRange(unit_t type, unsigned int& minRange, unsigned int& maxRange);
	static unsigned int getDefense(unit_t type);
	static unsigned int getMaxMps(unit_t type);


	//	INFO PARTICULAR DE CADA UNIDAD
	unit_t getType();		//infantry, mech, tank...
	unitType_t getBasicType();	//tread, foot or wheel
	unsigned int getCost();

	bool isAlive();
	virtual bool isReduced();
	bool hasValidActions();
	player_t getPlayer();
	Point getPosition();
	void heal();

	bool isActionValid(Action * act);

	virtual unsigned int getTerrainMod(terrain_t t) = 0; // si es UINT MAX es que no puede pasar
	virtual unsigned int getAttackMod(unitType_t basicType) = 0;	//devuelve el mod, dependiendo de si la unit esta o no reducida
	virtual unsigned int restoreMPs() = 0;		//pone los mps en el maximo de la unidad, devuelve los mps

	//move y attack hacen minimo control sobre si lo que le decis que hagan lo pueden hacer. la idea es que uses algo que vino de getPossibleActions
	bool move(Action m);
	int attack(Attack a, unsigned int diceRoll);	//de esto falta calcular el danio!

	void getPossibleActions(std::list<Action *>& actions);

protected:
	const unit_t type;
	const bool isMine;			//true si es de esta compu, false si es del otro jugador
	//si todavia no se si la compu es jugador 1 o 2: si es true es jugador 1

	const unsigned int minRange;
	const unsigned int maxRange;
	const unsigned int defense;
	const unsigned int cost;

	unitState_t state;
	unsigned int movingPoints;
	unsigned int healthPoints;


	//eventualmente las unidades pueden agregar mas variables: por ej que otras unidades estan cargando

	Point position; //en que tile estoy

	static Map * map;	//todas las units comparten el mismo map
	static std::unordered_map<unit_t, Unit *> info;

	void getPossibleMoves(std::list<Action *>& moves, Point start, Point curr, unsigned int movingPoints);
	void getPossibleAttacks(bool * newAttacks, std::list<Action *>& attacks, Point position, unsigned int movingPoints = 0);
};