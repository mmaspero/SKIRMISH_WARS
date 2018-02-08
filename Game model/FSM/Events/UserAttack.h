#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class UserAttack : public SkirmishEvent
{
public:
	UserAttack(Point target);
	const Point target;
};