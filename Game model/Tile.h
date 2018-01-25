#pragma once
#include "types.h"
#include "../Point.h"
#include "Unit.h"
#include "Building.h"

class Unit;

class Tile 
{
public:
	friend class Map;
	friend class tileObserver;

	Tile(Point position, terrain_t t);	//pone u y b en null, fog en true
	~Tile();			//hace delete de u y b (ver si lo dejamos aca o que)

	void update();

	player_t hasUnit();		//si devuelve NEUTRAL es que no hay
	Point getPosition();
	terrain_t getTerrain();	//si tiene edificio va a devolver ROAD

	bool setUnit(Unit * u);			//estas funciones verifican que no metas dos edificios o dos units en la misma tile
	bool setBuilding(Building * b);

	void removeFog(player_t p);


private:
	const Point position;
	const terrain_t t;		//si tiene un edificio esta variable no importa, el terreno es como road
	tileStatus_t status;
	bool opponentCanSee;
	Unit * u;
	Building * b;
	tileObserver * observer;
};