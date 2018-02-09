#include "WaitingMoveAck.h"
#include "UserMoving.h"
#include "WaitingAckTurnOver.h"
#include "skirmishHandlers.h"

WaitingMoveAck::WaitingMoveAck() : GenericState(WAITING_MOVE_ACK)
{
	;
}

GenericState * WaitingMoveAck::onTimeout(GenericEvent *)
{
	return new WaitingAckTurnOver();
}

GenericState * WaitingMoveAck::onAck(GenericEvent * ev)
{
	return new UserMoving();
}

GenericState * WaitingMoveAck::onUserPass(GenericEvent *)
{
	return new WaitingAckTurnOver();
}

GenericState * WaitingMoveAck::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * WaitingMoveAck::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingMoveAck::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingMoveAck::onUnselect(GenericEvent *)
{
	return this;
}
