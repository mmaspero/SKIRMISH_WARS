#pragma once
#include "types.h"
#include "../Point.h"
#include "Unit.h"
#include "Building.h"

class Unit;

class Tile //asldkfaoisdfn
{
public:
	friend class Map;

	Tile(Point position, terrain_t t = N_TERRAINS);	//pone u y b en null, fog en true
	~Tile();			//hace delete de u y b (ver si lo dejamos aca o que)
	void update();
	player_t hasUnit(); //si devuelve NEUTRAL es que no hay

	bool setTerrain(terrain_t t);//solo puedo llamarla cuando el terreno esta en none, no se puede llamar con none como arg
	bool setUnit(Unit * u);			//estas funciones verifican que no metas dos edificios o dos units en la misma tile
	bool setBuilding(Building * b);

	void removeFog();	//como estan ahora, no se fijan si habia o no fog antes
	void putFog();		//eventualmente, habria que notificar al viewer dependiendo si cambia algo o no

private:
	const Point position;
	terrain_t t;
	bool fog;
	Unit * u;
	Building * b;
};