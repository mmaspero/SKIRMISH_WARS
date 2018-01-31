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

bool Player::wasDefeated()
{
	return ((capturePointsHQ == 0) || (nUnits == 0));
}

unsigned int Player::getMoney()
{
	return money;
}

void Player::setObserver(playerObserver * obs)
{
	if (this->obs == nullptr && obs != nullptr) {
		this->obs = obs;
		obs->update();
	}
}
