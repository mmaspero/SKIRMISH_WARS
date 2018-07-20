#include "SkirmishFsm.h"
#include "FsmInfo.h"

SkirmishFSM::SkirmishFSM() : GenericFSM()
{
	;
}

SkirmishFSM::SkirmishFSM(GenericState * state) : GenericFSM(state)
{
	;
}

SkirmishFSM::~SkirmishFSM()
{
	;
}

void SkirmishFSM::dispatch(GenericEvent * ev)
{
	if (currentState == nullptr|| currentState->name() == FSM_CRASHED || ev == nullptr)
		return;

	GenericState * newState = nullptr;

	switch (ev->getType())
	{
	case EV_TIMEOUT:			{ newState = currentState->onTimeout(ev); }				break;
	case EV_ACK:				{ newState = currentState->onAck(ev); }					break;
	case EV_USER_PASS:			{ newState = currentState->onUserPass(ev); }			break;
	case EV_USER_ATTACK:		{ newState = currentState->onUserAttack(ev); }			break;
	case EV_USER_MOVE:			{ newState = currentState->onUserMove(ev); }			break;
	case EV_GO_TO_PURCHASE:		{ newState = currentState->onGoToPurchase(ev); }		break;
	case EV_USER_PURCHASE:		{ newState = currentState->onUserPurchase(ev); }		break;
	case EV_OPP_PASS:			{ newState = currentState->onOpponentPass(ev); }		break;
	case EV_OPP_ATTACK:			{ newState = currentState->onOpponentAttack(ev); }		break;
	case EV_OPP_MOVE:			{ newState = currentState->onOpponentMove(ev); }		break;
	case EV_OPP_PURCHASE:		{ newState = currentState->onOpponentPurchase(ev); }	break;
	case EV_PURCH_SELECTION:	{ newState = currentState->onPurchaseSelection(ev); }	break;
	case EV_UNIT_SELECTION:		{ newState = currentState->onUnitSelection(ev); }		break;
	case EV_UNSELECT:			{ newState = currentState->onUnselect(ev); }			break;
	}

	if (newState != nullptr && newState->name() != currentState->name()) {
		delete currentState;
		currentState = newState;
	}
}

state_t SkirmishFSM::state()
{
	if (currentState != nullptr)
		return currentState->name();
	else 
		return N_STATES;

}

GenericState const * SkirmishFSM::getState()
{
	return currentState;
}

