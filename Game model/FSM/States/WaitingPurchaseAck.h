#pragma once
#include "../GenericState.h"

class WaitingPurchaseAck : public GenericState {
public:
	WaitingPurchaseAck();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onAck(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
};