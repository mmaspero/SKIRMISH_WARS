#include "WaitingAckTurnOver.h"
#include "OpponentMoving.h"

WaitingAckTurnOver::WaitingAckTurnOver() : GenericState(WAITING_ACK_TURN_OVER)
{
	;
}

GenericState * WaitingAckTurnOver::onAck(GenericEvent& ev)
{
	return new OpponentMoving();
}
