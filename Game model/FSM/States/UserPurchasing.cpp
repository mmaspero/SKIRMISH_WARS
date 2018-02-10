#include "UserPurchasing.h"
#include "OpponentMoving.h"
#include "PurchaseSelected.h"
#include "../Events/PurchaseSelection.h"
#include "skirmishHandlers.h"

UserPurchasing::UserPurchasing() : GenericState(USER_PURCHASING)
{
	;
}

GenericState * UserPurchasing::onTimeout(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UserPurchasing::onUserPass(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UserPurchasing::onPurchaseSelection(GenericEvent *ev)
{
	((SkirmishEvent*)ev)->model()->showAvailableFactories();
	return new PurchaseSelected(((PurchaseSelection *)ev)->selection);
}

GenericState * UserPurchasing::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * UserPurchasing::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * UserPurchasing::onUnselect(GenericEvent *)
{
	return this;
}
