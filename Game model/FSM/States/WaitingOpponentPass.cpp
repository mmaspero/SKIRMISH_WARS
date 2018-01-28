#include "WaitingOpponentPass.h"
#include "UserMoving.h"

WaitingOpponentPass::WaitingOpponentPass() : GenericState(WAITING_OPP_PASS)
{
	;
}

GenericState * WaitingOpponentPass::onOpponentPass(GenericEvent *)
{
	return new UserMoving();
}
