#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class OpponentAttack : public SkirmishEvent
{
public:
	OpponentAttack(Point attacker, Point target, unsigned int dice);
	const Point attacker, target;
	const unsigned int dice;
};