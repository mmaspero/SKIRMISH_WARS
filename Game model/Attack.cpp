#include "Attack.h"

Attack::Attack(Point target, Point whereFrom, unsigned int mps) : Action (ACT_ATTACK, whereFrom, mps)
{
	this->target = target;
}