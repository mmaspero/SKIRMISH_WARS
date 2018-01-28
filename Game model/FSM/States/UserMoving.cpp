#include "UserMoving.h"
#include "OpponentMoving.h"
#include "UnitSelected.h"
#include "UserPurchasing.h"

UserMoving::UserMoving() : GenericState(USER_MOVING)
{
	;
}

GenericState * UserMoving::onTimeout(GenericEvent&)
{
	return new OpponentMoving();
}

GenericState * UserMoving::onUserPass(GenericEvent&)
{
	return new OpponentMoving();
}

GenericState * UserMoving::onGoToPurchase(GenericEvent&)
{
	return new UserPurchasing();
}

GenericState * UserMoving::onUnitSelection(GenericEvent&)
{
	return new UserPurchasing();
}

GenericState * UserMoving::onUnselect(GenericEvent &)
{
	return this;
}
