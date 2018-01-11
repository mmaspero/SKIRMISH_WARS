#include "Move.h"

Move::Move(Point target, unsigned int mps)
{
	this->whereTo = target;
	this->mps = mps;
}
