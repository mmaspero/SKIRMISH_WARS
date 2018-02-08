#pragma once
#include "GenericFSM.h"

class SkirmishFSM : public GenericFSM
{
public:
	SkirmishFSM();
	SkirmishFSM(GenericState * state);

	~SkirmishFSM();
	virtual void dispatch(GenericEvent * ev);

	state_t state();
	const GenericState * getState();
};