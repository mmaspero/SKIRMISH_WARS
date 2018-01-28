#include "WaitingAttackTurnOver.h"
#include "OpponentMoving.h"

WaitingAttackTurnOver::WaitingAttackTurnOver() : GenericState(WAITING_ATTACK_TURN_OVER)
{
	;
}

GenericState * WaitingAttackTurnOver::onOpponentAttack(GenericEvent &)
{
	return new OpponentMoving();
}
