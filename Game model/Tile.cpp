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

void Tile::update(player_t next)
{
	bool mustUpdate = false;

	if (u != nullptr) {
		u->nextTurn();

		if (b != nullptr) { //los edificios solo hacen cosas si tienen units
			if (u->getPlayer() == b->getPlayer()) {
				//si la unit y el building son del mismo equipo: la unidad se cura
				mustUpdate = u->heal();
			}
			else if (u->getBasicType() == FOOT) {
				//las unidades tipo FOOT pueden capturar edificios del enemigo o neutrales
				b->capture(u->isReduced(), u->getPlayer());
				mustUpdate = true; 
			}
		}
	}

	if (mustUpdate && obs != nullptr) {
		obs->update();
	}
}

void Tile::notifyObserver(void)
{
	if (obs != nullptr)
		obs->update();
}

bool Tile::hasUnit()
{	
	return u != nullptr;
}

bool Tile::hasBuilding()
{
	return b != nullptr;
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

bool Tile::canPurchaseUnit(player_t player)
{
	return (u == nullptr && b != nullptr && b->getPlayer() == player && b->getType() == FACTORY);
}

bool Tile::hasFog(player_t player)
{
	return (player == USER ? (status == FOG) : !(opponentCanSee));
}

bool Tile::setUnit(Unit * u)
{
	if (this->u == nullptr) {
		this->u = u;
		removeFog(u->getPlayer());
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
