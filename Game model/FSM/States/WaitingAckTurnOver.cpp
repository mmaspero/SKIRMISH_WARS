#include "WaitingAckTurnOver.h"
#include "OpponentMoving.h"
#include "skirmishHandlers.h"

WaitingAckTurnOver::WaitingAckTurnOver() : GenericState(WAITING_ACK_TURN_OVER)
{
	;
}

GenericState * WaitingAckTurnOver::onTimeout(GenericEvent *)
{
	return this;
}

GenericState * WaitingAckTurnOver::onAck(GenericEvent * ev)
{
	skirmishHandler::nextTurn((SkirmishEvent*)ev);
	return new OpponentMoving();
}

GenericState * WaitingAckTurnOver::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * WaitingAckTurnOver::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * WaitingAckTurnOver::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingAckTurnOver::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingAckTurnOver::onUnselect(GenericEvent *)
{
	return this;
}
