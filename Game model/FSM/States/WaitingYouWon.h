#pragma once
#include "../GenericState.h"

class WaitingYouWon : public GenericState {
public:
	WaitingYouWon();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
	GenericState * onYouWon(GenericEvent *);
};