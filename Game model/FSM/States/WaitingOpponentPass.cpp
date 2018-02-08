#include "WaitingOpponentPass.h"
#include "UserMoving.h"
#include "skirmishHandlers.h"

WaitingOpponentPass::WaitingOpponentPass() : GenericState(WAITING_OPP_PASS)
{
	;
}

GenericState * WaitingOpponentPass::onOpponentPass(GenericEvent *ev)
{
	skirmishHandler::nextTurn((SkirmishEvent*)ev);
	return new UserMoving();
}

GenericState * WaitingOpponentPass::onTimeout(GenericEvent *)
{
	return this;
}

GenericState * WaitingOpponentPass::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * WaitingOpponentPass::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * WaitingOpponentPass::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingOpponentPass::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingOpponentPass::onUnselect(GenericEvent *)
{
	return this;
}
