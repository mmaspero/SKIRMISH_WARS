#include "Tile.h"
#include "../view/gui.h"

Tile::Tile(Point position, terrain_t t) : position(position), t(t)
{
	u = nullptr;
	b = nullptr;
	status = FOG;
	opponentCanSee = false;
	obs = nullptr;
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

	if (obs != nullptr) {
		delete obs;
		obs = nullptr;
	}
}

void Tile::update()
{
	if (b != nullptr) {
		if (u != nullptr) {
			if ( u->getBasicType() == FOOT && u->getPlayer() != b->getPlayer()) {
			//las unidades tipo FOOT pueden capturar edificios del enemigo o neutrales
				b->capture(u->isReduced(), u->getPlayer());
				if (obs != nullptr) {
					obs->update();
				}
			}
			else {
				//si no, es que la unit y el building son del mismo equipo: la unidad se cura
				u->heal();
				if (obs != nullptr) {
					obs->update();
				}
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

Unit * Tile::getUnit()
{
	return u;
}

Building * Tile::getBuilding()
{
	return b;
}

bool Tile::setUnit(Unit * u)
{
	if (this->u == nullptr) {
		this->u = u;
		if (obs != nullptr) {
			obs->update();
		}
		return true;
	}
	else
		return false;
}

bool Tile::setBuilding(Building * b)
{
	if (this->b == nullptr) {
		this->b = b;

		if (obs != nullptr) {
			obs->update();
		}
		return true;
	}
	else
		return false;
}

void Tile::setObserver(tileObserver * obs)
{
	if (this->obs == nullptr && obs != nullptr) {
		obs = obs;
		obs->update();
	}
}

void Tile::removeFog(player_t p)
{
	if (p == USER && status == FOG) {
		status = VISIBLE;
		if (obs != nullptr) {
			obs->update();
		}
	}
	else if (p == OPPONENT && opponentCanSee == false) {
		opponentCanSee = true;
	}
}

void Tile::removeUnit()
{
	if (u != nullptr) {
		u = nullptr;
		if (obs != nullptr) {
			obs->update();
		}
	}
}
