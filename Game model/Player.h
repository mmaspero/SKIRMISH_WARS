#pragma once
#include "Unit.h"
#include "../view/playerObserver.h"

class Unit;

class Player {
public:
	friend class playerObserver;

	Player(player_t who, bool iStart);
	~Player();

	void nextState();
	Unit * buy(unit_t type, Point p);
	void collectIncome();	//IMPORTANTE! llamar antes de a nextState cuando se pasa 
	bool registerCapture(bool won, building_t type); //devuelve false si perdio sus hq
	//"won" es true si es un edificio que capture yo, y false si es uno que me capturaron
	//si hay un error tambien devuelve false (igual hay que cerrar todo)

	void setObserver(playerObserver * obs);
	void updateStats(unsigned int capturePointsHQ, unsigned int nFactories, unsigned int nCities, unsigned int nUnits);
	void unitKilled();

	bool wasDefeated();
	unsigned int getMoney();
	unsigned int getStatus();
	player_t id();

private:
	unsigned int money;
	unsigned int capturePointsHQ;
	unsigned int nFactories;
	unsigned int nCities;			//para calcular cuanto se gana de plata por turno
	unsigned int nUnits;			//todas! para ver cuando llegamos a cero

	const player_t who;
	playerStatus_t status;
	playerObserver * obs;
};