#include "Attack.h"

Attack::Attack(Point target, Point whereFrom, unsigned int mps) : Action (ATTACK, whereFrom, mps)
{
	this->target = target;
}