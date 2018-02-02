#include "Action.h"

Action::Action(action_t type, Point target, unsigned int mps) : type(type)
{
	this->whereTo = target;
	this->mps = mps;
}

action_t Action::basicType()
{
	if (type < ACT_ATTACK)
		return ACT_MOVE;
	else if (type < N_ACTIONS)
		return ACT_ATTACK;
	else
		return N_ACTIONS;
}
