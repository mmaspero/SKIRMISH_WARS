#include "skirmishHandlers.h"
#include "OpponentPurchasing.h"
#include "WaitingOpponentPass.h"
#include "UserMoving.h"
#include "../Events/OpponentPurchase.h"


OpponentPurchasing::OpponentPurchasing() : GenericState(OPP_PURCHASING)
{
	;
}

GenericState * OpponentPurchasing::onTimeout(GenericEvent *)
{
	//SkirmishEvent * ev = (SkirmishEvent *)e;
	//ev->contr()->stopPlayTimer(); ?
	return new WaitingOpponentPass();
}

GenericState * OpponentPurchasing::onUserPass(GenericEvent *)
{
	return this;
}

GenericState * OpponentPurchasing::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * OpponentPurchasing::onOpponentPass(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new UserMoving();
}

GenericState * OpponentPurchasing::onOpponentPurchase(GenericEvent * e)
{
	OpponentPurchase * ev = (OpponentPurchase *)e;
	ev->model()->registerPurchase(OPPONENT, ev->p, ev->type);
	//ev->contr()->resetPlayTimer();
	//ev->contr()->sendOneBytePackage(ACK);
	return this;
}

GenericState * OpponentPurchasing::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentPurchasing::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentPurchasing::onUnselect(GenericEvent *)
{
	return this;
}
