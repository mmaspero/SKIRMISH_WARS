#include "Tile.h"

Tile::Tile(Point position, terrain_t t) : position(position), t(t)
{
	u = nullptr;
	b = nullptr;
	status = FOG;
	opponentCanSee = false;
	observer = nullptr;
}

Tile::~Tile()
{
	if (b != nullptr) {
		delete b;
		b = nullptr;
	}

	if (u != nullptr) {
		delete u;
		u = nullptr;
	}
}

void Tile::update()
{
	if (b != nullptr) {
		if (u != nullptr) {
			if ( u->getBasicType() == FOOT && u->getPlayer() != b->getPlayer()) {
			//las unidades tipo FOOT pueden capturar edificios del enemigo o neutrales
				b->capture(u->isReduced(), u->getPlayer());
			}
			else {
				//si no, es que la unit y el building son del mismo equipo: la unidad se cura
				u->heal();
			}
		}
	}
}

player_t Tile::hasUnit()
{	
	return (u==nullptr? NEUTRAL : u->getPlayer());
}

Point Tile::getPosition()
{
	return position;
}

terrain_t Tile::getTerrain()
{
	if (b == nullptr)
		return t;
	else
		return ROAD;
}

bool Tile::setUnit(Unit * u)
{
	if (this->u == nullptr) {
		this->u = u;
		return true;
	}
	else
		return false;
}

bool Tile::setBuilding(Building * b)
{
	if (this->b == nullptr) {
		this->b = b;
		return true;
	}
	else
		return false;
}

void Tile::removeFog(player_t p)
{
	if (p == USER && status == FOG) {
		status = VISIBLE;
	}
	else if (p == OPPONENT && opponentCanSee == false) {
		opponentCanSee = true;
	}
}
