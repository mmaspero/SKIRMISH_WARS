#pragma once
#include "../GenericState.h"

class WaitingAckTurnOver : public GenericState {
public:
	WaitingAckTurnOver();

	GenericState * onAck(GenericEvent *);
};