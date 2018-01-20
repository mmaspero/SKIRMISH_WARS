#include "Move.h"

Action::Action(action_t type, Point target, unsigned int mps) : type(type)
{
	this->whereTo = target;
	this->mps = mps;
}
