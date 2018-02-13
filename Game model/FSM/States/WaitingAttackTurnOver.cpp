#include "WaitingAttackTurnOver.h"
#include "OpponentMoving.h"
#include "WaitingYouWon.h"
#include "skirmishHandlers.h"

WaitingAttackTurnOver::WaitingAttackTurnOver(Point user, Point opponent) : UserAttacking(user, opponent)
{
	;
}

GenericState * WaitingAttackTurnOver::onTimeout(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onUnselect(GenericEvent *)
{
	return this;
}

GenericState * WaitingAttackTurnOver::onOpponentAttack(GenericEvent * e)
{
	SkirmishEvent * ev = (SkirmishEvent *)e;
	ev->model()->endAttack(user);
	skirmishHandler::nextTurn(ev);
	return new OpponentMoving();
}

GenericState * WaitingAttackTurnOver::onWaitForYouWon(GenericEvent * ev)
{
	((SkirmishEvent*)ev)->model()->endAttack(opponent);
	return new WaitingYouWon();
}
