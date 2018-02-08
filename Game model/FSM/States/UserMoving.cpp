#include "UserMoving.h"
#include "OpponentMoving.h"
#include "UnitSelected.h"
#include "UserPurchasing.h"
#include "../SkirmishEvent.h"
#include "../Events/UnitSelection.h"
#include "skirmishHandlers.h"

UserMoving::UserMoving() : GenericState(USER_MOVING)
{
	;
}

GenericState * UserMoving::onTimeout(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UserMoving::onUserPass(GenericEvent *e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UserMoving::onGoToPurchase(GenericEvent *)
{
	return new UserPurchasing();
}

GenericState * UserMoving::onUnitSelection(GenericEvent * e)
{
	UnitSelection* ev = (UnitSelection*)e;
	ev->model()->showPossibleActions(ev->tile);
	return new UnitSelected(ev->tile);
}

GenericState * UserMoving::onUnselect(GenericEvent *)
{
	return this;
}
