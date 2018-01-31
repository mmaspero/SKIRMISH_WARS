#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class UserMove : public SkirmishEvent
{
public:
	UserMove(Point p0, Point pf);
	const Point p0, pf;
};