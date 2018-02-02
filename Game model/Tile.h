#pragma once
#include "types.h"
#include "../Point.h"
#include "Unit.h"
#include "Building.h"
#include "../view/tileObserver.h"

class Unit;

class Tile 
{
public:
	friend class Map;
	friend class tileObserver;

	Tile(Point position, terrain_t t);	//pone u y b en null, fog en true
	~Tile();			//hace delete de u y b (ver si lo dejamos aca o que)

	void update(player_t next);		//si se capturo un edificio, devuelve quien era el duenio de antes. si no, N_PLAYERS
	void notifyObserver(void);

	bool hasUnit();	
	bool hasBuilding();
	Point getPosition();
	terrain_t getTerrain();	//si tiene edificio va a devolver ROAD
	Unit * getUnit();
	Building * getBuilding();
	bool canPurchaseUnit(player_t player);
	bool hasFog(player_t player);

	bool setUnit(Unit * u);			//estas funciones verifican que no metas dos edificios o dos units en la misma tile
	bool setBuilding(Building * b);
	void setObserver(tileObserver * obs);

	void removeFog(player_t p);
	void removeUnit();

private:
	const Point position;
	const terrain_t t;		//si tiene un edificio esta variable no importa, el terreno es como road
	tileStatus_t status;
	bool opponentCanSee;
	Unit * u;
	Building * b;
	tileObserver * obs;
};