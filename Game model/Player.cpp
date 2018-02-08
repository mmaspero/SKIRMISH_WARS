#include "Player.h"
#include "Units\AntiAir.h"
#include "Units\Apc.h"
#include "Units\Artillery.h"
#include "Units\Infantry.h"
#include "Units\Mech.h"
#include "Units\MedTank.h"
#include "Units\Recon.h"
#include "Units\Rocket.h"
#include "Units\Tank.h"

#define INIT_MONEY	5	//VER DONDE DEJAMOS ESTE DEFINE

Player::Player(player_t who) : who(who)
{
	capturePointsHQ = nUnits = nCities = nFactories = 0;
	money = INIT_MONEY;
	obs = nullptr;
}

Player::~Player()
{
	;
}

Unit * Player::buy(unit_t type, Point p)
{
	unsigned int cost = UINT_MAX;
	Unit * u = nullptr;

	if (status == PURCHASING && Unit::getCost(type) <= money) {
		u = Unit::factory(type, p, who == USER);
		if (u != nullptr) {
			money -= Unit::getCost(type);
			nUnits++;
			if (obs != nullptr) {
				obs->update();
			}
		}
	}

	return u;
}

void Player::collectIncome()
{
	if (!wasDefeated()) {
		money += (nCities + 1)*INIT_MONEY;
		if (obs != nullptr) {
			obs->update();
		}
	}
}

bool Player::registerCapture(bool won, building_t type)
{
	switch (type) {
	case CITY: { won ? nCities++ : nCities--; } break;
	case FACTORY: {won ? nFactories++ : nFactories--; } break;
	case HEADQUARTERS: { if (!won) capturePointsHQ = 0;  } break;
	}

	if (nCities > B_H * B_W || nFactories > B_H * B_W) { //ERROR! tenia 0 de ese edificio y reste
		capturePointsHQ = 0;
	}

	return (capturePointsHQ != 0);
}

bool Player::wasDefeated()
{
	return ((capturePointsHQ == 0) || (nUnits == 0));
}

unsigned int Player::getMoney()
{
	return money;
}

player_t Player::id()
{
	return who;
}

void Player::setObserver(playerObserver * obs)
{
	if (this->obs == nullptr && obs != nullptr) {
		this->obs = obs;
		obs->update();
	}
}

void Player::updateStats(unsigned int capturePointsHQ, unsigned int nFactories, unsigned int nCities, unsigned int nUnits)
{
	bool newStats = false;

	if (this->capturePointsHQ != capturePointsHQ) {
		this->capturePointsHQ = capturePointsHQ;
		newStats = true;
	}

	if (this->nFactories != nFactories) {
		this->nFactories = nFactories;
		newStats = true;
	}
	if (this->nCities != nCities) {
		this->nCities = nCities;
		newStats = true;
	}
	if (this->nUnits != nUnits) {
		this->nUnits = nUnits;
		newStats = true;
	}

	if (newStats && obs != nullptr) {
		obs->update();
	}
}

void Player::unitKilled()
{
	if (nUnits)
		nUnits--;
}
