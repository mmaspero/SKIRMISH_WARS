#pragma once
#include "../GenericState.h"

class UserPurchasing : public GenericState {
public:
	UserPurchasing();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
};