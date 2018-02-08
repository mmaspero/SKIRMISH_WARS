#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class UserMove : public SkirmishEvent
{
public:
	UserMove(Point pf);
	const Point pf;
};