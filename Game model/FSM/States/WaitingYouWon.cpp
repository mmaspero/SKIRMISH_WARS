#include "WaitingYouWon.h"

WaitingYouWon::WaitingYouWon() : GenericState(WAITING_YOU_WON)
{
	;
}

GenericState * WaitingYouWon::onTimeout(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onUnselect(GenericEvent *)
{
	return this;
}

GenericState * WaitingYouWon::onYouWon(GenericEvent *)
{
	
	return nullptr;
}
