#pragma once
#include "types.h"

typedef enum buildings { HEADQUARTERS, FACTORY } building_t;

class Building {
public:
	Building(building_t type, player_t player = NEUTRAL);
	//falta: setear capture points segun type

	~Building();	//no hace nada

	player_t getPlayer();
	bool isBeingCaptured();
	bool capture(bool isReduced, player_t player) { return true; } //despues vemos que hace si capturas mal
	void repair() { ; }

private:
	building_t type;
	player_t player;
	unsigned int capturePoints;
};