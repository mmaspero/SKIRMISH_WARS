#pragma once
#include "types.h"

class Building {
public:
	Building(building_t type, player_t player = NEUTRAL);
	//falta: setear capture points segun type

	~Building();	//no hace nada

	player_t getPlayer();
	bool isBeingCaptured();
	bool capture(bool isReduced, player_t player); //devuelve true si cambio de equipos
	void uncapture();

private:
	building_t type;
	player_t player;
	unsigned int capturePoints;
};