#include "Tile.h"

Tile::Tile(Point position, terrain_t t) : position(position)
{
	this->t = t;
	u = nullptr;
	b = nullptr;
	fog = true;
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
		b->repair();

		if (u != nullptr) {
			if (b->getPlayer() == NEUTRAL || (u->getPlayer() != b->getPlayer())) {
				//capturo si el edificio es neutral, o si el jugador del edificio no es el mismo que el de la unit
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

bool Tile::setTerrain(terrain_t t)
{
	if (this->t == N_TERRAINS && t != N_TERRAINS) {
		this->t = t;
		return true;
	}
	else
		return false;
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

void Tile::removeFog()
{
	fog = false;
}

void Tile::putFog()
{
	fog = true;
}
