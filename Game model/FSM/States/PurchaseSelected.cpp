#include "PurchaseSelected.h"
#include "OpponentMoving.h"
#include "UserPurchasing.h"

PurchaseSelected::PurchaseSelected() : GenericState(PURCHASE_SELECTED)
{
	;
}

GenericState * PurchaseSelected::onTimeout(GenericEvent&)
{
	return new OpponentMoving();
}

GenericState * PurchaseSelected::onUserPass(GenericEvent &)
{
	return new OpponentMoving();
}

GenericState * PurchaseSelected::onUserPurchase(GenericEvent&)
{
	return new UserPurchasing();
}

GenericState * PurchaseSelected::onGoToPurchase(GenericEvent &)
{
	return new UserPurchasing();
}

GenericState * PurchaseSelected::onPurchaseSelection(GenericEvent &)
{
	return this;	//o crear otro estado purchase selected?
}

GenericState * PurchaseSelected::onUnitSelection(GenericEvent &)
{
	return new UserPurchasing();
}

GenericState * PurchaseSelected::onUnselect(GenericEvent&)
{
	return new UserPurchasing();
}
