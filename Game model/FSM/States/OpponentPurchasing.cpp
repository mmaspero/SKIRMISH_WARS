#include "OpponentPurchasing.h"
#include "WaitingOpponentPass.h"
#include "UserMoving.h"

OpponentPurchasing::OpponentPurchasing() : GenericState(OPP_PURCHASING)
{
	;
}

GenericState * OpponentPurchasing::onTimeout(GenericEvent&)
{
	return new WaitingOpponentPass();
}

GenericState * OpponentPurchasing::onUserPass(GenericEvent &)
{
	return this;
}

GenericState * OpponentPurchasing::onGoToPurchase(GenericEvent &)
{
	return this;
}

GenericState * OpponentPurchasing::onOpponentPass(GenericEvent&)
{
	return new UserMoving();
}

GenericState * OpponentPurchasing::onOpponentPurchase(GenericEvent&)
{
	return this;
}

GenericState * OpponentPurchasing::onPurchaseSelection(GenericEvent &)
{
	return this;
}

GenericState * OpponentPurchasing::onUnitSelection(GenericEvent &)
{
	return this;
}

GenericState * OpponentPurchasing::onUnselect(GenericEvent &)
{
	return this;
}
