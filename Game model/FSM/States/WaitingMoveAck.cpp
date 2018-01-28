#include "WaitingMoveAck.h"
#include "UserMoving.h"
#include "WaitingAckTurnOver.h"

WaitingMoveAck::WaitingMoveAck() : GenericState(WAITING_MOVE_ACK)
{
	;
}

GenericState * WaitingMoveAck::onTimeout(GenericEvent *)
{
	return new WaitingAckTurnOver();
}

GenericState * WaitingMoveAck::onAck(GenericEvent *)
{
	return new UserMoving();
}

GenericState * WaitingMoveAck::onUserPass(GenericEvent *)
{
	return new WaitingAckTurnOver();
}
