#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class UserAttack : public SkirmishEvent
{
public:
	UserAttack(Point attacker, Point target);
	const Point attacker, target;
};