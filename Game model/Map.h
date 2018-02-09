#pragma once
#include "Tile.h"
#include "Unit.h"
#include "Building.h"
#include "types.h"
#include "../Point.h"
#include "unitInfo.h"
#include <list>
#include <utility>

class Tile;
class Unit;

class Map 
{
public:
	Map(const char * csvPath, player_t first);
	~Map();
	bool isValid();

	terrain_t getTerrain(Point p);
	player_t getUnitPlayer(Point p);
	player_t getBuildingPlayer(Point p);
	basicUnitType_t getBasicType(Point p);
	Unit * getUnit(Point p);
	Building * getBuilding(Point p);

	static bool isInMap(Point p); //para verificar que un punto no se vaya de rango
	bool hasUnit(Point p);
	bool hasBuilding(Point p);
	bool hasFog(Point p, player_t player);
	bool canSeeUnit(Point p, player_t player);
	bool canPurchaseUnit(Point p, player_t player);	//no le da bola al costo, solo que haya una fabrica vacia
	bool canBoard(Point p, player_t player);
	bool canCapture(Point p, player_t player);

	void update(player_t next);
	bool updateUnitPos(Unit * u, Point newPosition);	//llamarla antes de cambiar la posicion de la unidad!
	//si la posicion anterior no era valida no pasa nada, lo importante es la nueva
	//si es una unidad nueva dejar la posicion nueva adentro de la unit tambien
//	bool newUnit(Unit * u);
	void clearTile(Point p); //saca la unidad
	void revealUnit(Point p, player_t player);
	void hideUnit(Point p, player_t player);
	void showAction(Point p, action_t act);
	void notifyTileObserver(Point p);
	void select(Point p);
	void unselect(Point p);
	void playerInfo(player_t who, unsigned int& capturePointsHQ, unsigned int& nFactories, unsigned int& nCities, unsigned int &nUnits);


private:
	Tile * board[B_H][B_W];

	void removeFog(Point p, player_t player);
	bool valid;

	friend class Model;
};
