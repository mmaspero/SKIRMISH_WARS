#pragma once
#include "Unit.h"
#include "../view/playerObserver.h"

class Unit;

class Player {
public:
	friend class playerObserver;

	Player(player_t who);
	~Player();

	Unit * buy(unit_t type, Point p);
	void collectIncome();

	void setObserver(playerObserver * obs);

	bool wasDefeated();
	unsigned int getMoney();

private:
	unsigned int money;
	unsigned int capturePointsHQ;
	unsigned int nCities;			//para calcular cuanto se gana de plata por turno
	unsigned int nUnits;			//todas! para ver cuando llegamos a cero
	const player_t who;
	playerStatus_t status;
	playerObserver * obs;
};