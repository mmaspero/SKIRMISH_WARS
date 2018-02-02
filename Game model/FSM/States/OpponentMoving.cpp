#include "OpponentMoving.h"
#include "OpponentPurchasing.h"
#include "WaitingOpponentPass.h"
#include "UserMoving.h"
#include "../Events/OpponentMove.h"
#include "../Events/OpponentAttack.h"

OpponentMoving::OpponentMoving() : GenericState(OPP_MOVING)
{
	;
}

GenericState * OpponentMoving::onTimeout(GenericEvent *)
{
	//ev->contr()->stopPlayTimer(); ?
	return new WaitingOpponentPass();
}

GenericState * OpponentMoving::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onOpponentPass(GenericEvent * e)
{
	SkirmishEvent * ev = (SkirmishEvent *)e;
	ev->model()->nextTurn();
	//ev->contr()->resetPlayTimer();
	return new UserMoving();
}

GenericState * OpponentMoving::onOpponentAttack(GenericEvent * e)
{
	OpponentAttack * ev = (OpponentAttack *)e;
	
	return this;
}

GenericState * OpponentMoving::onOpponentMove(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onOpponentPurchase(GenericEvent *)
{
	return new OpponentPurchasing();
}

GenericState * OpponentMoving::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onUnselect(GenericEvent *)
{
	return this;
}