#pragma once
#include "../GenericState.h"

class WaitingAttackTurnOver : public GenericState {
public:
	WaitingAttackTurnOver();

	GenericState * onOpponentAttack(GenericEvent&);
};