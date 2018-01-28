#pragma once
#include "../GenericState.h"

class OpponentPurchasing : public GenericState {
public:
	OpponentPurchasing();

	GenericState * onTimeout(GenericEvent&);
	GenericState * onUserPass(GenericEvent&);
	GenericState * onGoToPurchase(GenericEvent&);
	GenericState * onOpponentPass(GenericEvent&);
	GenericState * onOpponentPurchase(GenericEvent&);
	GenericState * onPurchaseSelection(GenericEvent&);
	GenericState * onUnitSelection(GenericEvent&);
	GenericState * onUnselect(GenericEvent&);
};