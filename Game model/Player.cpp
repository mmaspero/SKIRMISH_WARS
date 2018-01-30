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

std::list<Unit *> Player::unitInfo;


Player::Player(player_t who) : who(who)
{
	money = INIT_MONEY;
	obs = nullptr;
	if (who == USER) {
		Point p(B_H, B_W); //posicion default para poder crear las unidades
		unitInfo.push_back(new AntiAir(p, true)); //el true indica el jugador, no importa
		unitInfo.push_back(new Apc(p, true));
		unitInfo.push_back(new Artillery(p, true));
		unitInfo.push_back(new Infantry(p, true));
		unitInfo.push_back(new Mech(p, true));
		unitInfo.push_back(new MedTank(p, true));
		unitInfo.push_back(new Recon(p, true));
		unitInfo.push_back(new Rocket(p, true));
		unitInfo.push_back(new Tank(p, true));
	}

}

Unit * Player::buy(unit_t type, Point p)
{
	unsigned int cost = UINT_MAX;
	Unit * u = nullptr;

	for (std::list<Unit *>::iterator it = unitInfo.begin(); it != unitInfo.end(); it++) {
		if ((*it)->getType() == type) {
			cost = (*it)->getCost();
		}
	}

	if (status == PURCHASING && cost <= money) {
		u = Unit::factory(type, p, who == USER);
		if (u != nullptr) {
			money -= cost;
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

std::list<Unit *> Player::getPossiblePurchases()
{
	return unitInfo;
}

void Player::setObserver(playerObserver * obs)
{
	if (this->obs == nullptr && obs != nullptr) {
		this->obs = obs;
		obs->update();
	}
}
