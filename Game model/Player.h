#pragma once
#include "Unit.h"
#include <list>
#include <utility>

class Player {
public:
	friend class playerObserver;

	Player(player_t who);
	~Player() { ; }

	bool buy(unit_t type, Point p);
	void collectIncome();
	bool wasDefeated();
	std::list<Unit *> getPossiblePurchases();

private:
	unsigned int money;
	unsigned int capturePointsHQ;
	unsigned int nCities;			//para calcular cuanto se gana de plata por turno
	unsigned int nUnits;			//todas! para ver cuando llegamos a cero
	const player_t who;
	playerStatus_t status;
	playerObserver * observer;

	static std::list<Unit *> unitInfo;
};