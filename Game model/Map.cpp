#include "Map.h"
#include "Units\Apc.h"
#include "Unit.h"
#include "../Csv.h"
#include "unitInfo.h"
#include <unordered_map>
#include <algorithm>

terrain_t parseTerrain(std::string s); 
Unit * parseUnit(std::string s, Point p, player_t first);
Building * parseBuilding(std::string s, Point p, player_t first);


Map::Map(char * csvPath, player_t first)
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
						removeFog(p, board[p.x][p.y]->u->getPlayer());
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
		return board[p.x][p.y]->getTerrain();
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
	if (valid && isInMap(p) && (board[p.x][p.y]->u) != nullptr)
		return ((board[p.x][p.y])->u)->getBasicType();
	else
		return N_B_TYPES;
}

Unit * Map::getUnit(Point p)
{
	if (valid && isInMap(p))
		return board[p.x][p.y]->u;
	else
		return nullptr;
}

bool Map::hasUnit(Point p)
{
	if (valid && isInMap(p) && (board[p.x][p.y]->u) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasBuilding(Point p)
{
	if (valid && isInMap(p) && (board[p.x][p.y]->b) != nullptr)
		return true;
	else
		return false;
}

bool Map::hasFog(Point p, player_t player)
{
	if (valid && isInMap(p))
		return (player==USER? (board[p.x][p.y]->status == FOG) : !(board[p.x][p.y]->opponentCanSee));
	else
		return false;
}

bool Map::updateUnitPos(Unit * u, Point p, bool intoAPC)
{
	bool valid = this->valid;	
	Point oldPos;

	if (valid && u != nullptr && isInMap(p)) {
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
	bool valid = this->valid;

	if (valid && u != nullptr) {
		Point p = u->getPosition();
		if (isInMap(p) && board[p.x][p.y]->u == nullptr) {
			valid = true;
			board[p.x][p.y]->u = u;
			
			removeFog(u->getPosition(), u->getPlayer());
		}
	}

	return valid; 
}

void Map::clearTile(Point p)
{
	if (valid && isInMap(p)) {
		board[p.x][p.y]->removeUnit();
	}
}

void Map::removeFog(Point p, player_t player)
{
	if (valid && isInMap(p)) {
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
	if (p.x < B_H && p.y < B_W && p.x >= 0 && p.y >= 0)
		return true;
	else
		return false;
}

terrain_t parseTerrain(std::string s)
{
	if (s.size() == 1) {
		switch (s[0]) {
		case GRASS_CHR:		return GRASS;
		case RIVER_CHR:		return RIVER;
		case ROAD_CHR:		return ROAD;
		case FOREST_CHR:	return FOREST;
		case HILL_CHR:		return HILL;

		default:			return N_TERRAINS;
		}
	}
	else
		return N_TERRAINS;
}

Unit * parseUnit(std::string s, Point p, player_t first)
{
	Unit * u = nullptr;

	if (s.size() == 3 && (s[2] == '1' || s[2] == '2')) {
		bool isMine = (s[2] == '1' && first == USER);
		s.pop_back();

		std::unordered_map<std::string, unit_t> units;
		units.emplace(std::string(RE_STR), RECON);
		units.emplace(std::string(RO_STR), ROCKET);
		units.emplace(std::string(ME_STR), MECH);
		units.emplace(std::string(IN_STR), INFANTRY);
		units.emplace(std::string(TA_STR), TANK);
		units.emplace(std::string(AR_STR), ARTILLERY);
		units.emplace(std::string(AA_STR), ANTIAIR);
		units.emplace(std::string(AP_STR), APC);
		units.emplace(std::string(MT_STR), MEDTANK);


		std::unordered_map<std::string, unit_t>::const_iterator it = units.find(s);
		if (it != units.end()) {
			u = Unit::factory(it->second, p, isMine);
		}
	}

	return u;
}

Building * parseBuilding(std::string s, Point p, player_t first)
{
	Building * b = nullptr;

	if (s.size() == 2 && (s[1] >= '0' || s[1] <= '2')) {
		player_t player = (s[1] == '0' ? NEUTRAL : (s[1] == '1' && first == USER ? USER : OPPONENT));

		switch (s[0]) {
		case HQ_CHR: { b = new Building(HEADQUARTERS, player); } break;
		case FACTORY_CHR: { b = new Building(FACTORY, player); } break;
		case CITY_CHR: { b = new Building(CITY, player); } break;
		}

	}

	return b;
}
