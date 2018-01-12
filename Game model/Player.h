#pragma once
#include "Unit.h"
#include <list>
#include <utility>

class Player {
public:
	friend class playerObserver;
	Player();
	~Player();

	bool buy(unit_t type);
	void collectIncome();
	bool wasDefeated();
	std::list<std::pair<Unit, unsigned int>> getPossiblePurchases();

private:
	unsigned int money;
	unsigned int capturePointsHQ;
	unsigned int nCities;			//para calcular cuanto se gana de plata por turno
	unsigned int nUnits;			//todas! para ver cuando llegamos a cero
	player_t who;
	playerStatus_t status;
};