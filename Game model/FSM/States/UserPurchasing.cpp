#include "UserPurchasing.h"
#include "OpponentMoving.h"
#include "PurchaseSelected.h"

UserPurchasing::UserPurchasing() : GenericState(USER_PURCHASING)
{
	;
}

GenericState * UserPurchasing::onTimeout(GenericEvent *)
{
	return new OpponentMoving();
}

GenericState * UserPurchasing::onUserPass(GenericEvent *)
{
	return new OpponentMoving();
}

GenericState * UserPurchasing::onPurchaseSelection(GenericEvent *)
{
	return new PurchaseSelected();
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
