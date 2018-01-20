#include "Map.h"
#include "Units\Apc.h"

Map::Map()
{
	for (unsigned int i = 0; i < B_H; i++) {
		for (unsigned int j = 0; j < B_W; j++) {
			board[i][j] = new Tile(Point(i,j), GRASS);
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

bool Map::hasFog(Point p, player_t player)
{
	if (isInMap(p))
		return (player==USER? (board[p.x][p.y]->status == FOG) : !(board[p.x][p.y]->opponentCanSee));
	else
		return false;
}

bool Map::updateUnitPos(Unit * u, Point p, bool intoAPC)
{
	bool valid = true;	
	Point oldPos;

	if (u != nullptr && isInMap(p)) {
		oldPos = u->getPosition();
		
		if (intoAPC && board[p.x][p.y]->u->getType() == APC && (board[p.x][p.y]->u->getPlayer() == u->getPlayer())) {
			((Apc *)board[p.x][p.y]->u)->load(u);
		}
		else if ( (board[p.x][p.y]->u) == nullptr) {
			player_t player = u->getPlayer();
			board[p.x][p.y]->u = u;	//si la muevo a una tile vacia, update de la posicion
		}
		else {
			valid = false;
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
	bool valid = false;

	if (u != nullptr) {
		Point p = u->getPosition();
		if (isInMap(p)) {
			valid = true;
			board[p.x][p.y]->u = u;
			
			removeFog(u->getPosition(), u->getPlayer());
		}
	}

	return valid; 
}

void Map::removeFog(Point p, player_t player)
{
	if (isInMap(p)) {
		board[p.x][p.y]->removeFog(player);

		p.x--;
		if (isInMap(p))
			board[p.x][p.y]->removeFog(player);

		p.x += 2;
		if (isInMap(p))
			board[p.x][p.y]->removeFog(player);
		
		p.x--; p.y--;
		if (isInMap(p))
			board[p.x][p.y]->removeFog(player);

		p.y += 2;
		if (isInMap(p))
			board[p.x][p.y]->removeFog(player);
	}
}

bool Map::isInMap(Point p)
{
	if (p.x < B_W && p.y < B_W && p.x >= 0 && p.y >= 0)
		return true;
	else
		return false;
}
