#pragma once
#include "../GenericState.h"

class OpponentMoving : public GenericState
{
public:
	OpponentMoving();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onOpponentPass(GenericEvent *);
	GenericState * onOpponentAttack(GenericEvent *);
	GenericState * onOpponentMove(GenericEvent *);
	GenericState * onOpponentPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);

};