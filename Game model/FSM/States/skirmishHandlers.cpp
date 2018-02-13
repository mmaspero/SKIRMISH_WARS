#include "skirmishHandlers.h"
#include "../FsmInfo.h"

void skirmishHandler::nextTurn(SkirmishEvent * ev)
{
	ev->model()->nextTurn();
	//ev->contr()->resetPlayTimer();
	if (ev->getType() != EV_OPP_PASS) {
		ev->contr()->sendOneBytePackage(PASS);
	}
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
