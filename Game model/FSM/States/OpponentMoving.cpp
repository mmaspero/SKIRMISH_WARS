#include "OpponentMoving.h"
#include "OpponentPurchasing.h"
#include "WaitingOpponentPass.h"
#include "UserMoving.h"

OpponentMoving::OpponentMoving() : GenericState(OPP_MOVING)
{
	;
}

GenericState * OpponentMoving::onTimeout(GenericEvent&)
{

	return new WaitingOpponentPass();
}

GenericState * OpponentMoving::onUserPass(GenericEvent &)
{
	return this;
}

GenericState * OpponentMoving::onGoToPurchase(GenericEvent &)
{
	return this;
}

GenericState * OpponentMoving::onOpponentPass(GenericEvent&)
{
	return new UserMoving();
}

GenericState * OpponentMoving::onOpponentAttack(GenericEvent&)
{
	return this;
}

GenericState * OpponentMoving::onOpponentMove(GenericEvent&)
{
	return this;
}

GenericState * OpponentMoving::onOpponentPurchase(GenericEvent&)
{
	return new OpponentPurchasing();
}

GenericState * OpponentMoving::onPurchaseSelection(GenericEvent &)
{
	return this;
}

GenericState * OpponentMoving::onUnitSelection(GenericEvent &)
{
	return this;
}

GenericState * OpponentMoving::onUnselect(GenericEvent &)
{
	return this;
}
