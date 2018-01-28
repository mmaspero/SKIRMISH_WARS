#include "WaitingPurchaseAck.h"
#include "WaitingAckTurnOver.h"
#include "UserPurchasing.h"

WaitingPurchaseAck::WaitingPurchaseAck() : GenericState(WAITING_PURCH_ACK)
{
	;
}

GenericState * WaitingPurchaseAck::onTimeout(GenericEvent *)
{
	return new WaitingAckTurnOver();
}

GenericState * WaitingPurchaseAck::onAck(GenericEvent *)
{
	return new UserPurchasing();
}

GenericState * WaitingPurchaseAck::onUserPass(GenericEvent *)
{
	return new WaitingAckTurnOver();
}
