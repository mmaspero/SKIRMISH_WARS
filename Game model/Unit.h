#pragma once
#include "unitInfo.h"
#include "types.h"
#include "Attack.h"
#include "Map.h"
#include <list>

typedef enum unitStates { IDLE, MOVING, ATTACKING, UNLOADING, POST_ACTIVE, N_UNIT_STATES } unitState_t;
//idle: todavia no se movio
//moving: se movio al menos una vez, puede que haya mas movimientos validos. ya esta activa
//attacking: ya ataco, esta esperando el contra-ataque

class Map;
class Tile;

class Unit	//cada unidad especifica va a heredar de esta y definir como ataca y como se mueve
{
public:
	Unit(unit_t type, Point position, bool isMine, unsigned int cost,
		unsigned int defense, unsigned int minRange, unsigned int maxRange);		
	~Unit();	//no hace nada
	//virtual??

	static Unit * factory(unit_t type, Point position, bool isMine);
	static void setMap(Map * map);

	unit_t getType();		//infantry, mech, tank...
	unitType_t getBasicType();	//tread, foot or wheel
	unsigned int getCost();

	bool isAlive();
	virtual bool isReduced();
	player_t getPlayer();
	Point getPosition();
	void heal();

	virtual int getTerrainMod(terrain_t t) = 0; // si es UINT MAX es que no puede pasar
	virtual unsigned int getAttackMod(unitType_t basicType) = 0;	//devuelve el mod, dependiendo de si la unit esta o no reducida
	virtual unsigned int restoreMPs() = 0;		//pone los mps en el maximo de la unidad, devuelve los mps

	//move y attack hacen minimo control sobre si lo que le decis que hagan lo pueden hacer. la idea es que uses algo que vino de getPossibleActions
	bool move(Action m);
	int attack(Attack a, unsigned int diceRoll);	//de esto falta calcular el danio!

	void getPossibleActions(std::list<Action>& moves, std::list<Attack>& attacks);
	//todos! no tiene en cuenta la fog, eventualmente se puede agregar

protected:
	const unit_t type;
	const bool isMine;			//true si es de esta compu, false si es del otro jugador
	//si todavia no se si la compu es jugador 1 o 2: si es true es jugador 1

	//unsigned int terrainMod[N_TERRAINS+1];	//dejo uno para poder tener una posicion que sea solo para error
	//unsigned int attackMod[N_B_TYPES+1];
	//unsigned int redAttackMod[N_B_TYPES+1];
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

	void getPossibleMoves(std::list<Action>& moves, Point start, Point curr, unsigned int movingPoints);
	void getPossibleAttacks(bool * newAttacks, std::list<Attack>& attacks, Point position, unsigned int movingPoints = 0);
	//FALTAN OBSERVERS!!!
};
