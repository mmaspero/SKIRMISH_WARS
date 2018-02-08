#include "skirmishHandlers.h"

void skirmishHandler::nextTurn(SkirmishEvent * ev)
{
	ev->model()->nextTurn();
	//ev->contr()->resetPlayTimer();
}

void skirmishHandler::registerAttack(SkirmishEvent * ev)
{
	if (ev->getType() == EV_OPP_ATTACK) {

	}
	else if (ev->getType() == EV_USER_ATTACK) {

	}
	else {
		return;
	}
}
