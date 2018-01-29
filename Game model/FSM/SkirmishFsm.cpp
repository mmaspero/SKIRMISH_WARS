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
	if (currentState == nullptr || ev == nullptr)
		return;

	GenericState * newState = nullptr;

	switch (ev->getType())
	{
	case TIMEOUT:			{ newState = currentState->onTimeout(ev); }			break;
	case ACK:				{ newState = currentState->onAck(ev); }				break;
	case USER_PASS:			{ newState = currentState->onUserPass(ev); }			break;
	case USER_ATTACK:		{ newState = currentState->onUserAttack(ev); }			break;
	case USER_MOVE:			{ newState = currentState->onUserMove(ev); }			break;
	case USER_PURCHASE:		{ newState = currentState->onUserPurchase(ev); }		break;
	case OPP_PASS:			{ newState = currentState->onOpponentPass(ev); }		break;
	case OPP_ATTACK:		{ newState = currentState->onOpponentAttack(ev); }		break;
	case OPP_MOVE:			{ newState = currentState->onOpponentMove(ev); }		break;
	case OPP_PURCHASE:		{ newState = currentState->onOpponentPurchase(ev); }	break;
	case PURCH_SELECTION:	{ newState = currentState->onPurchaseSelection(ev); }	break;
	case UNIT_SELECTION:	{ newState = currentState->onUnitSelection(ev); }		break;
	case UNSELECT:			{ newState = currentState->onUnselect(ev); }			break;
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
