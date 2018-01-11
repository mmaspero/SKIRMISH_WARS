#include "Player.h"

#define INIT_MONEY	5	//VER DONDE DEJAMOS ESTE DEFINE




Player::Player()
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
	return (!areHQstanding || !bool(nUnits));
}
