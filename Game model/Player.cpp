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
}

void Player::collectIncome()
{
	if (!wasDefeated()) {
		money += (nCities + 1)*INIT_MONEY;
	}
}

bool Player::wasDefeated()
{
	return (!bool(capturePointsHQ) || !bool(nUnits));
}

std::list<Unit *> Player::getPossiblePurchases()
{
	std::list<Unit *> purch;
	Point p(1, 1); //posicion default para poder crear las unidades
	purch.push_back(new AntiAir(p, true)); //el true indica el jugador, no importa
	purch.push_back(new Apc(p, true));
	purch.push_back(new Artillery(p, true));
	purch.push_back(new Infantry(p, true));
	purch.push_back(new Mech(p, true));
	purch.push_back(new MedTank(p, true));
	purch.push_back(new Recon(p, true));
	purch.push_back(new Rocket(p, true));
	purch.push_back(new Tank(p, true));

	return purch;
}
