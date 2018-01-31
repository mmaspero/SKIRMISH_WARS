#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class OpponentMove : public SkirmishEvent
{
public:
	OpponentMove(Point p0, Point pf);
	const Point p0, pf;
};