#pragma once
#include "../GenericState.h"

class WaitingMoveAck : public GenericState {
public:
	WaitingMoveAck();

	GenericState * onTimeout(GenericEvent *);
	GenericState * onAck(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
};