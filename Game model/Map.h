#pragma once
#include "Tile.h"
#include "Unit.h"
#include "types.h"
#include "../Point.h"
#include "unitInfo.h"

#define B_W	12
#define	B_H	16

class Tile;
class Unit;

class Map 
{
public:
	Map(); //se le podria pasar el path del archivo
	~Map();

	terrain_t getTerrain(Point p);
	player_t getPlayer(Point p);
	unitType_t getBasicType(Point p);
	Unit * getUnit(Point p);

	static bool isInMap(Point p); //para verificar que un punto no se vaya de rango
	bool hasUnit(Point p);
	bool hasBuilding(Point p);
	bool hasFog(Point p);

	void update();
	bool updateUnitPos(Unit * u, Point newPosition, bool intoAPC = false);	//llamarla antes de cambiar la posicion de la unidad!
	bool newUnit(Unit * u);

private:
	Tile * board[B_H][B_W]; 
};
