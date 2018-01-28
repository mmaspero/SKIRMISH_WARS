#pragma once
#include "../GenericState.h"

class PurchaseSelected : public GenericState {
public:
	PurchaseSelected();

	GenericState * onTimeout(GenericEvent&);
	GenericState * onUserPass(GenericEvent&);
	GenericState * onUserPurchase(GenericEvent&);
	GenericState * onGoToPurchase(GenericEvent&);
	GenericState * onPurchaseSelection(GenericEvent&);
	GenericState * onUnitSelection(GenericEvent&);
	GenericState * onUnselect(GenericEvent&);
};