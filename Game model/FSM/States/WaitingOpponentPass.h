#pragma once
#include "../GenericState.h"

class WaitingOpponentPass : public GenericState {
public:
	WaitingOpponentPass();

	GenericState * onOpponentPass(GenericEvent *);
	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
};