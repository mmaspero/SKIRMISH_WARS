#include "UserAttacking.h"
#include "WaitingAttackTurnOver.h"
#include "UserMoving.h"

UserAttacking::UserAttacking() : GenericState(USER_ATTACKING)
{
	;
}

GenericState * UserAttacking::onTimeout(GenericEvent&)
{
	return new WaitingAttackTurnOver();
}

GenericState * UserAttacking::onUserPass(GenericEvent&)
{
	return new WaitingAttackTurnOver();
}

GenericState * UserAttacking::onOpponentAttack(GenericEvent&)
{
	return new UserMoving();
}

GenericState * UserAttacking::onGoToPurchase(GenericEvent &)
{
	return this;
}

GenericState * UserAttacking::onPurchaseSelection(GenericEvent &)
{
	return this;
}

GenericState * UserAttacking::onUnitSelection(GenericEvent &)
{
	return this;
}

GenericState * UserAttacking::onUnselect(GenericEvent &)
{
	return this;
}
