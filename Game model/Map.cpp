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
						removeFog(p, getUnitPlayer(p));
					}
					if ((hasBuilding(p) && getBuildingPlayer(p) != NEUTRAL)) {
						removeFog(p, getBuildingPlayer(p));
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

void Map::update(player_t next)
{
	if (valid) {
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				board[i][j]->update(next);
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

player_t Map::getUnitPlayer(Point p)
{
	if (isInMap(p) && hasUnit(p))
		return ((board[p.row][p.col])->u)->getPlayer();
	else
		return NEUTRAL;
}

player_t Map::getBuildingPlayer(Point p)
{
	if (hasBuilding(p))
		return board[p.row][p.col]->b->getPlayer();
	else
		return N_PLAYERS;
}

basicUnitType_t Map::getBasicType(Point p)
{
	if (valid && hasUnit(p))
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

Building * Map::getBuilding(Point p)
{
	if (valid && isInMap(p))
		return board[p.row][p.col]->b;
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
	return valid && isInMap(p) && board[p.row][p.col]->hasFog(player);
}

bool Map::canSeeUnit(Point p, player_t player)
{
	return valid && isInMap(p) && board[p.row][p.col]->canSeeUnit(player);
}

bool Map::canPurchaseUnit(Point p, player_t player)
{
	return (valid && isInMap(p) && board[p.row][p.col]->canPurchaseUnit(player));
}

bool Map::canBoard(Point p, player_t player)
{
	bool ans = false;

	if (valid && isInMap(p) && hasUnit(p) && getUnit(p)->getType() == APC) {
		Apc * apc = (Apc *)getUnit(p);
		ans = apc->canBoard(player);
	}

	return ans;
}

bool Map::canCapture(Point p, player_t player)
{
	return (valid && hasBuilding(p) && getBuildingPlayer(p) != player);
}

bool Map::updateUnitPos(Unit * u, Point p)
{
	bool valid = this->valid;	
	Point oldPos;

	if (valid && u != nullptr && isInMap(p)) {
		oldPos = u->getPosition();
		
		if (hasUnit(p)) { 
			if (u->getBasicType() == FOOT && canBoard(p, u->getPlayer())) {
				((Apc *)board[p.row][p.col]->u)->load(u); //unico caso que puede haber mas de una unidad en una tile
				board[p.row][p.col]->notifyObserver(); //me saltie a la tile! notificar!
			}
			else {
				valid = false;
			}
		}
		else {
			if (u->getBasicType() == FOOT && canCapture(p, u->getPlayer())) {
				board[p.row][p.col]->b->capture(u, u->getPlayer());
			}
			board[p.row][p.col]->setUnit(u);
			removeFog(p, u->getPlayer());
		}
	}

	if (valid && oldPos != p && isInMap(oldPos) && board[oldPos.row][oldPos.col]->u == u) {
		clearTile(oldPos); //saco la unidad de donde estaba antes
	}

	return valid;
}

//bool Map::newUnit(Unit * u)
//{
//	bool valid = this->valid;
//
//	if (valid && u != nullptr && isInMap(u->getPosition())) {
//		Point p = u->getPosition();
//		if (board[p.row][p.col]->u == nullptr) {
//			valid = true;
//			board[p.row][p.col]->u = u;
//			
//			removeFog(u->getPosition(), u->getPlayer());
//		}
//	}
//
//	return valid; 
//}

void Map::clearTile(Point p)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->removeUnit();
	}
}

void Map::revealUnit(Point p, player_t player)
{
	if (valid && isInMap(p))
		board[p.row][p.col]->revealUnit(player);
}

void Map::hideUnit(Point p, player_t player)
{
	if (valid && isInMap(p))
		board[p.row][p.col]->hideUnit(player);
}

void Map::showAction(Point p, action_t act)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->showAction(act);
	}
}

void Map::notifyTileObserver(Point p)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->notifyObserver();
	}
}

void Map::select(Point p)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->select();
	}
}

void Map::unselect(Point p)
{
	if (valid && isInMap(p)) {
		board[p.row][p.col]->unselect();
	}
}

void Map::playerInfo(player_t who, unsigned int& capturePointsHQ, unsigned int & nFactories, unsigned int & nCities, unsigned int & nUnits)
{
	capturePointsHQ = nUnits = nCities = nFactories = 0;
	if (valid && (who == USER || who == OPPONENT)) {
		for (unsigned int i = 0; i < B_H; i++) {
			for (unsigned int j = 0; j < B_W; j++) {
				Point p(i, j);

				if (getBuildingPlayer(p) == who) { //esto nunca va a ser true si no hay edificio!
					switch (board[p.row][p.col]->b->getType()) {
					
					case CITY: { 
						nCities++; 
					} break;
					
					case FACTORY: {
						nFactories++;
					} break;
					
					case HEADQUARTERS:	{ 
						capturePointsHQ = board[p.row][p.col]->b->getCapturePoints();
					} break;

					}
				}

				if (getUnitPlayer(p) == who) {
					nUnits++;
				}
			}
		}
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
		bool isMine = ((s.back() == '2') ^ (first == USER));
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
		player_t player = (s[1] == '0' ? NEUTRAL : ( ((s[1] == '2') ^ (first == USER)) ? USER : OPPONENT) );
		building_t type = parseBuildingChar(s[0]);
		
		if (type < N_BUILDINGS) { 
			b = new Building(type, player);
		}
	}

	return b;
}
