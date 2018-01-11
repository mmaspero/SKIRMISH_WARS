#include "Map.h"

Map::Map()
{
	for (unsigned int i = 0; i < B_H; i++) {
		for (unsigned int j = 0; j < B_W; j++) {
			board[i][j] = new Tile(Point(i,j), GRASS);
			board[i][j]->b = nullptr;
			board[i][j]->u = nullptr;
			board[i][j]->fog = true;
		}
	}
}


Map::~Map()
{

}

void Map::update()
{
	for (unsigned int i = 0; i < B_H; i++) {
		for (unsigned int j = 0; j < B_W; j++) {
			board[i][j]->update();
 
			if (board[i][j]->hasUnit() == USER) { //para las unidades del jugador, sacar la fog
				for (unsigned int ii = (i == 0 ? i : i - 1); ii < (i == B_H - 1 ? i : i + 1); ii++)
					for (unsigned int jj = (j == 0 ? j : j - 1); jj < (j == B_W - 1 ? j : j + 1); jj++)
						board[ii][jj]->removeFog();
			}
		}
	}
}

terrain_t Map::getTerrain(Point p)
{
	if (isInMap(p))
		return board[p.x][p.y]->t;
	else
		return N_TERRAINS;
}

player_t Map::getPlayer(Point p)
{
	if (isInMap(p))
		return ((board[p.x][p.y])->u)->getPlayer();
	else
		return NEUTRAL;
}

unitType_t Map::getBasicType(Point p)
{
	if (isInMap(p) && (board[p.x][p.y]->u) != nullptr)
		return ((board[p.x][p.y])->u)->getBasicType();
	else
		return N_B_TYPES;
}

Unit * Map::getUnit(Point p)
{
	if (isInMap(p))
		return board[p.x][p.y]->u;
	else
		return nullptr;
}

bool Map::hasUnit(Point p)
{
	if (isInMap(p) && (board[p.x][p.y]->u) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasBuilding(Point p)
{
	if (isInMap(p) && (board[p.x][p.y]->b) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasFog(Point p)
{
	if (isInMap(p))
		return board[p.x][p.y]->fog;
	else
		return false;
}

bool Map::updateUnitPos(Unit * u, Point p, bool intoAPC)
{
	bool valid = false;	
	Point oldPos;

	if (u != nullptr && isInMap(p)) {
		oldPos = u->getPosition();
		
		if (intoAPC) {
			if (board[p.x][p.y]->u->getType() == APC && (board[p.x][p.y]->u->getPlayer() == u->getPlayer()) ) {
				valid = true;
			}
		}
		else if ( (board[p.x][p.y]->u) == nullptr) {
				board[p.x][p.y]->u = u;	//si la muevo a una tile vacia, update de la posicion
				valid = true;
		}
	}

	if (valid && isInMap(oldPos) && board[oldPos.x][oldPos.y]->u == u) {
		board[oldPos.x][oldPos.y]->u = nullptr; // si la unidad estaba donde me dijeron, la saco. si no,
		//puede que viniera de un apc (o que estuviera mal desde antes) y lo dejo con lo que haya
	}

	return valid;
}

bool Map::newUnit(Unit * u)
{
	if (u != nullptr) {
		Point p = u->getPosition();
		if (isInMap(p)) {
			board[p.x][p.y]->u = u;
			return true;
		}
	}

	return false; 
}

bool Map::isInMap(Point p)
{
	if (p.x < B_W && p.y < B_W && p.x >= 0 && p.y >= 0)
		return true;
	else
		return false;
}
