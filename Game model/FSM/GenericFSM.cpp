#include "GenericFSM.h"

GenericFSM::GenericFSM()
{
	currentState = nullptr;
}

GenericFSM::GenericFSM(GenericState * firstState)
{
	currentState = firstState;
}

GenericFSM::~GenericFSM()
{
	if (currentState != nullptr)
		delete currentState;
}

void GenericFSM::setFirstState(GenericState * state)
{
	if (currentState == nullptr)
		currentState = state;
}
