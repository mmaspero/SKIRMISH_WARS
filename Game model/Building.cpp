#include "Building.h"

#define	CP_PER_TURN		2
#define RED_CP_PER_TURN	1	//reduced capture points

void setCapturePoints(building_t type, unsigned int& cp);


Building::Building(building_t type, player_t player) : type(type)
{
	this->player = player;

	setCapturePoints(type, capturePoints);
}

Building :: ~Building() { ; }

building_t Building::getType()
{
	return type;
}

player_t Building::getPlayer()
{
	return player;
}

player_t Building::capture(bool isReduced, player_t player) 
{ 
	unsigned int lostCps;
	player_t capturedFrom = N_PLAYERS;

	if (player != this->player) {
		if (isReduced)
			lostCps = RED_CP_PER_TURN;
		else
			lostCps = CP_PER_TURN;
			
		if (lostCps < capturePoints) {
			capturePoints -= lostCps;
		}
		else {
			setCapturePoints(type, capturePoints);
			capturedFrom = this->player;
			this->player = player;
		}
	}

	return capturedFrom;
}

void Building::uncapture()
{
	setCapturePoints(type, capturePoints);
}

unsigned int Building::getCapturePoints()
{
	return capturePoints;
}

bool Building::isBeingCaptured()
{
	unsigned int maxCp = 0;
	setCapturePoints(type, maxCp);
	return (capturePoints != maxCp);
}

void setCapturePoints(building_t type, unsigned int& cp)
{ 
	if (type == HEADQUARTERS)
		cp = CP_HQ;
	else
		cp = CP_DEFAULT;
}
