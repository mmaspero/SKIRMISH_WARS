#pragma once
#include "types.h"

class Building {
public:
	Building(building_t type, player_t player = NEUTRAL);
	//falta: setear capture points segun type

	~Building();	//no hace nada

	building_t getType();
	player_t getPlayer();
	bool isBeingCaptured();
	player_t capture(bool isReduced, player_t player); //si cambio de jugador, devuelve el duenio previo. si no, N_PLAYERS
	void uncapture();
	unsigned int getCapturePoints();

protected:
	const building_t type;
	player_t player;
	unsigned int capturePoints;
};