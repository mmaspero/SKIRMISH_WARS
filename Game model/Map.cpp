#include "Map.h"
#include "Units\Apc.h"
#include "Unit.h"
#include "../Csv.h"
#include "unitInfo.h"
#include <algorithm>
#include "../view/gui.h"

terrain_t parseTerrain(std::string s); 
Unit * parseUnit(std::string s, Point p, player_t first);
Building * parseBuilding(std::string s, Point p, player_t first);


Map::Map(const char * csvPath, player_t first)
{
	Csv csv(csvPath);
	valid = false;
	memset((void *)board, 0, B_H*B_W*sizeof(void *)); //pongo todos en null

	if (csv.getColumns() == B_W && csv.getRows() == B_H) {
	//aca ya verifico que estaba bien el archivo
		valid = true;
		for (unsigned int i = 0; i < B_H && valid; i++) {
			for (unsigned int j = 0; j < B_W && valid; j++) {
				std::string tile = csv.getCell(i, j);
				Point p(i, j);
				terrain_t t = ROAD;
				//building_t b = N_BUILDINGS;
				//unit_t u = N_UNIT_TYPES;
				Unit * u = nullptr;
				Building * b = nullptr;
				size_t unitString = 0;

				if (tile.size()) {
					std::transform(tile.begin(), tile.end(), tile.begin(), ::tolower);
					unitString = tile.find(UNIT_TOKEN);
					if (unitString != std::string::npos) {
						u = parseUnit(tile.substr(unitString+1, std::string::npos), p, first);
						if (u == nullptr) {
							valid = false;
						}
						else {
							tile = tile.substr(0, unitString);
						}
					}
					
					t = parseTerrain(tile);
					if (t >= N_TERRAINS) {
						t = ROAD;
						b = parseBuilding(tile, p, first);
						if (b == nullptr) {
							valid = false;
						}
					}
					
					if (valid) {
						board[i][j] = new Tile(p, t);
						if (u != nullptr) {
							board[i][j]->setUnit(u);
						}
						if (b != nullptr) {
							board[i][j]->setBuilding(b);
						}

					}
 				}
			}
		}	

		if(valid) { //sacar la fog donde corresponda. antes no podia porque no estaban
												//construidas todas las tiles
			for (unsigned int i = 0; i < B_H; i++) {
				for (unsigned int j = 0; j < B_W; j++) {
					Point p(i, j);
					if (hasUnit(p)) {
						removeFog(p, board[p.row][p.col]->u->getPlayer());
					}
				}
			}
		}
	}
}


Map::~Map()
{
	for (unsigned int i = 0; i < B_H; i++) {
		for (unsigned int j = 0; j < B_W; j++) {
			if (board[i][j] != nullptr) { //por si no pude construir bien todo
				delete board[i][j];
			}
		}
	}
}

bool Map::isValid()
{
	return valid;
}

void Map::update()
{
	if (valid) {
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				board[i][j]->update();
			}
		}
	}
}

terrain_t Map::getTerrain(Point p)
{
	if (valid && isInMap(p))
		return board[p.row][p.col]->getTerrain();
	else
		return N_TERRAINS;
}

player_t Map::getPlayer(Point p)
{
	if (isInMap(p))
		return ((board[p.row][p.col])->u)->getPlayer();
	else
		return NEUTRAL;
}

unitType_t Map::getBasicType(Point p)
{
	if (valid && isInMap(p) && (board[p.row][p.col]->u) != nullptr)
		return ((board[p.row][p.col])->u)->getBasicType();
	else
		return N_BASIC_U_TYPES;
}

Unit * Map::getUnit(Point p)
{
	if (valid && isInMap(p))
		return board[p.row][p.col]->u;
	else
		return nullptr;
}

bool Map::hasUnit(Point p)
{
	if (valid && isInMap(p) && (board[p.row][p.col]->u) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasBuilding(Point p)
{
	if (valid && isInMap(p) && (board[p.row][p.col]->b) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasFog(Point p, player_t player)
{
	if (valid && isInMap(p))
		return (player==USER? (board[p.row][p.col]->status == FOG) : !(board[p.row][p.col]->opponentCanSee));
	else
		return false;
}

bool Map::canPurchaseUnit(Point p, player_t player)
{
	return (valid && isInMap(p) && board[p.row][p.col]->canPurchaseUnit(player));
}

bool Map::updateUnitPos(Unit * u, Point p, bool intoAPC)
{
	bool valid = this->valid;	
	Point oldPos;

	if (valid && u != nullptr && isInMap(p)) {
		oldPos = u->getPosition();
		
		if (intoAPC && board[p.row][p.col]->u->getType() == APC && (board[p.row][p.col]->u->getPlayer() == u->getPlayer())) {
			((Apc *)board[p.row][p.col]->u)->load(u);
		}
		else if ( (board[p.row][p.col]->u) == nullptr) {
			player_t player = u->getPlayer();
			board[p.row][p.col]->u = u;	//si la muevo a una tile vacia, update de la posicion
		}
		else {
			valid = false;
		}
	}

	if (valid && isInMap(oldPos) && board[oldPos.row][oldPos.col]->u == u) {
		board[oldPos.row][oldPos.col]->u = nullptr; // si la unidad estaba donde me dijeron, la saco. si no,
		//puede que viniera de un apc (o que estuviera mal desde antes) y lo dejo con lo que haya
	}
	
	return valid;
}

bool Map::newUnit(Unit * u)
{
	bool valid = this->valid;

	if (valid && u != nullptr) {
		Point p = u->getPosition();
		if (isInMap(p) && board[p.row][p.col]->u == nullptr) {
			valid = true;
			board[p.row][p.col]->u = u;
			
			removeFog(u->getPosition(), u->getPlayer());
		}
	}

	return valid; 
}

void Map::clearTile(Point p)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->removeUnit();
	}
}

void Map::removeFog(Point p, player_t player)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->removeFog(player);

		p.row--;
		if (isInMap(p))
			board[p.row][p.col]->removeFog(player);

		p.row += 2;
		if (isInMap(p))
			board[p.row][p.col]->removeFog(player);
		
		p.row--; p.col--;
		if (isInMap(p))
			board[p.row][p.col]->removeFog(player);

		p.col += 2;
		if (isInMap(p))
			board[p.row][p.col]->removeFog(player);
	}
}

bool Map::isInMap(Point p)
{
	if (p.row < B_H && p.col < B_W && p.row >= 0 && p.col >= 0)
		return true;
	else
		return false;
}

terrain_t parseTerrain(std::string s)
{
	if (s.size() == 1) {
		return parseTerrainChar(s[0]);
	}
	else
		return N_TERRAINS;
}

Unit * parseUnit(std::string s, Point p, player_t first)
{
	Unit * u = nullptr;
	unit_t type = N_UNIT_TYPES;

	if (s.back() == '1' || s.back() == '2') {
		bool isMine = (s.back() == '1' && first == USER);
		s.pop_back();

		type = parseUnitString(s);
		if (type < N_UNIT_TYPES) {
			u = Unit::factory(type, p, isMine);
		}
	}

	return u;
}

Building * parseBuilding(std::string s, Point p, player_t first)
{
	Building * b = nullptr;

	if (s.size() == 2 && (s[1] >= '0' || s[1] <= '2')) {
		player_t player = (s[1] == '0' ? NEUTRAL : (s[1] == '1' && first == USER ? USER : OPPONENT));
		building_t type = parseBuildingChar(s[0]);
		
		if (type < N_BUILDINGS) { 
			b = new Building(type, player);
		}
	}

	return b;
}
