#pragma once
#include "Tile.h"
#include "Unit.h"
#include "types.h"
#include "../Point.h"
#include "unitInfo.h"
#include "../view/gui.h"

class Tile;
class Unit;
class gui;

class Map 
{
public:
	Map(char * csvPath, player_t first, gui * g);
	~Map();
	bool isValid();

	terrain_t getTerrain(Point p);
	player_t getPlayer(Point p);
	unitType_t getBasicType(Point p);
	Unit * getUnit(Point p);

	static bool isInMap(Point p); //para verificar que un punto no se vaya de rango
	bool hasUnit(Point p);
	bool hasBuilding(Point p);
	bool hasFog(Point p, player_t player);

	void update();	//FALTA QUE HAGA EL UPDATE SOLO DEL JUGADOR QUE EMPIEZA SU TURNO! que reciba player_t
	bool updateUnitPos(Unit * u, Point newPosition, bool intoAPC = false);	//llamarla antes de cambiar la posicion de la unidad!
	bool newUnit(Unit * u);
	void clearTile(Point p); //saca la unidad

private:
	Tile * board[B_H][B_W];

	void removeFog(Point p, player_t player);
	bool valid;
};
