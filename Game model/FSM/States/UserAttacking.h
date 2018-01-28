#pragma once
#include "../GenericState.h"

class UserAttacking : public GenericState {
public:
	UserAttacking();

	GenericState * onTimeout(GenericEvent&);
	GenericState * onUserPass(GenericEvent&);
	GenericState * onOpponentAttack(GenericEvent&);
	GenericState * onGoToPurchase(GenericEvent&);
	GenericState * onPurchaseSelection(GenericEvent&);
	GenericState * onUnitSelection(GenericEvent&);
	GenericState * onUnselect(GenericEvent&);
};