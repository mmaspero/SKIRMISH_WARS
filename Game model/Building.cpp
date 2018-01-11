#include "Building.h"

Building::Building(building_t type, player_t player)
{
	this->player = player;
	this->type = type;

	capturePoints = 0;	//setear segun type!

	//switch (type) {
	//case HEADQUARTERS:
	//	capturePoints = HQ_CP;
	//	break;

	//case FACTORY:
	//	capturePoints = FACT_CP;
	//	break;

	//}

}

Building :: ~Building() { ; }

player_t Building::getPlayer()
{
	return player;
}

bool Building::isBeingCaptured()
{
	return bool(capturePoints);
}
