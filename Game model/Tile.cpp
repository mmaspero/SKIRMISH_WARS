#include "Tile.h"
#include "../view/gui.h"

Tile::Tile(Point position, terrain_t t) : position(position), t(t)
{
	u = nullptr;
	b = nullptr;
	opponentStatus = status = FOG;
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

		if (next == u->getPlayer()) {
			if (b != nullptr) { //los edificios solo hacen cosas si tienen units
				if (next == b->getPlayer()) {
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
	return (player == USER ? (status == FOG || status == UNIT_REVEALED) : (opponentStatus == FOG || opponentStatus == UNIT_REVEALED));
}

bool Tile::canSeeUnit(player_t player)
{
	return (player == USER? (status != FOG) : (opponentStatus != FOG));
}

bool Tile::setUnit(Unit * u)
{
	if (this->u == nullptr) {
		this->u = u;
		removeFog(u->getPlayer());
		notifyObserver();
		return true;
	}
	else
		return false;
}

bool Tile::setBuilding(Building * b)
{
	if (this->b == nullptr) {
		this->b = b;

		notifyObserver();
		return true;
	}
	else
		return false;
}

void Tile::setObserver(tileObserver * obs)
{
	if (this->obs == nullptr && obs != nullptr) {
		this->obs = obs;
		obs->update();
	}
}

void Tile::removeFog(player_t p)
{
	if (p == USER && (status == FOG || status == UNIT_REVEALED)) {
		status = VISIBLE;
		notifyObserver();
	}
	else if (p == OPPONENT && (opponentStatus == FOG || opponentStatus == UNIT_REVEALED)) {
		opponentStatus = VISIBLE;
	}
}

void Tile::revealUnit(player_t p)
{
	if (p == USER && status == FOG) {
		status = UNIT_REVEALED;
		notifyObserver();
	}
	else if (p == OPPONENT && opponentStatus == FOG) {
		opponentStatus = UNIT_REVEALED;
	}
}

void Tile::hideUnit(player_t p)
{
	if (p == USER && status == UNIT_REVEALED) {
		status = FOG;
		notifyObserver();
	}
	else if (p == OPPONENT && opponentStatus == UNIT_REVEALED) {
		opponentStatus = FOG;
	}
}

void Tile::removeUnit()
{
	if (u != nullptr) {
		if (b != nullptr && b->getPlayer() != u->getPlayer()) {
			b->uncapture();
		}
		u = nullptr;
		notifyObserver();
	}
}

void Tile::showAction(action_t act)
{
	if (status != FOG) {
		switch (act) {
		case ACT_MOVE:		{ status = CAN_MOVE; }		break;
		case ACT_ATTACK:	{ status = CAN_ATTACK; }	break;
		default:			{ status = VISIBLE; }		break;
		}
		notifyObserver();
	}
}

void Tile::select()
{
	if (status == VISIBLE) {
		status = SELECTED;
		notifyObserver();
	}
}

void Tile::unselect()
{
	if (status == SELECTED) {
		status = VISIBLE;
		notifyObserver();
	}
}
