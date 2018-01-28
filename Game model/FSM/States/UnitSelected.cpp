#include "UnitSelected.h"
#include "OpponentMoving.h"
#include "UserMoving.h"
#include "UserPurchasing.h"
#include "UserAttacking.h"
#include "WaitingMoveAck.h"

UnitSelected::UnitSelected() : GenericState(UNIT_SELECTED)
{
}

GenericState * UnitSelected::onTimeout(GenericEvent *)
{
	return new OpponentMoving();
}

GenericState * UnitSelected::onUserPass(GenericEvent *)
{
	return new OpponentMoving();
}

GenericState * UnitSelected::onUserAttack(GenericEvent *)
{
	return new UserAttacking();
}

GenericState * UnitSelected::onUserMove(GenericEvent *)
{
	return new WaitingMoveAck();
}

GenericState * UnitSelected::onGoToPurchase(GenericEvent *)
{
	return new UserPurchasing();
}

GenericState * UnitSelected::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * UnitSelected::onPurchaseSelection(GenericEvent *)
{
	return new UserMoving();
}

GenericState * UnitSelected::onUnselect(GenericEvent *)
{
	return new UserMoving();
}
