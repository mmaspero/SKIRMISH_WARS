#pragma once
#include "../GenericState.h"

class WaitingMoveAck : public GenericState {
public:
	WaitingMoveAck();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onAck(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
};