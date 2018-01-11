#pragma once
#include "Unit.h"

class Player {
public:
	Player();
	~Player();

	bool buy(unit_t type);
	void collectIncome();
	bool wasDefeated();


private:
	unsigned int money;
	bool areHQstanding;
	unsigned int nCities;		//para calcular cuanto se gana de plata por turno
	unsigned int nUnits;		//todas! para ver cuando llegamos a cero
};