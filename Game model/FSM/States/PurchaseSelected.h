#pragma once
#include "../GenericState.h"
#include "../../types.h"

class PurchaseSelected : public GenericState {
public:
	PurchaseSelected(unit_t selection);

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onUserPurchase(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);

protected:
	const unit_t selection;
};