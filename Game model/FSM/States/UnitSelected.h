#pragma once
#include "../GenericState.h"

class UnitSelected : public GenericState {
public:
	UnitSelected();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onUserAttack(GenericEvent *);
	GenericState * onUserMove(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
};
