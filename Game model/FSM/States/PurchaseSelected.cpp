#include "skirmishHandlers.h"
#include "PurchaseSelected.h"
#include "OpponentMoving.h"
#include "UserPurchasing.h"
#include "WaitingPurchaseAck.h"
#include "../Events/UserPurchase.h"
#include "../Events/PurchaseSelection.h"
#include "../../types.h"

PurchaseSelected::PurchaseSelected(unit_t selection) : GenericState(PURCHASE_SELECTED), selection(selection)
{
	;
}

GenericState * PurchaseSelected::onTimeout(GenericEvent * ev)
{
	skirmishHandler::nextTurn((SkirmishEvent*)ev);
	return new OpponentMoving();
}

GenericState * PurchaseSelected::onUserPass(GenericEvent * ev)
{
	skirmishHandler::nextTurn((SkirmishEvent*)ev);
	return new OpponentMoving();
}

GenericState * PurchaseSelected::onUserPurchase(GenericEvent * e)
{
	UserPurchase * ev = (UserPurchase *)e;
	//ev->contr()->resetPlayTimer();
	//ev->contr()->sendPurchase(getUnitString(selection), ev->p.row, ev->p.col);
	ev->model()->registerPurchase(USER, ev->p, selection);
	return new WaitingPurchaseAck();
}

GenericState * PurchaseSelected::onGoToPurchase(GenericEvent * ev)
{
	return new UserPurchasing();
}

GenericState * PurchaseSelected::onPurchaseSelection(GenericEvent * ev)
{
	return new PurchaseSelected(((PurchaseSelection*)ev)->selection);
}

GenericState * PurchaseSelected::onUnitSelection(GenericEvent * ev)
{
	return new UserPurchasing();
}

GenericState * PurchaseSelected::onUnselect(GenericEvent * ev)
{
	return new UserPurchasing();
}
