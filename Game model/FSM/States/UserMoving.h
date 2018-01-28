#pragma once
#include "../GenericState.h"

class UserMoving : public GenericState {
public:
	UserMoving();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
};