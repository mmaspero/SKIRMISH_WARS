#pragma once
#include "../GenericState.h"

class WaitingOpponentPass : public GenericState {
public:
	WaitingOpponentPass();

	GenericState * onOpponentPass(GenericEvent&);
};