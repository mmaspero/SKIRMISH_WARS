#include "Attack.h"

Attack::Attack(Point target, Point whereFrom, unsigned int mps) : Move (whereFrom, mps)
{
	this->target = target;
}