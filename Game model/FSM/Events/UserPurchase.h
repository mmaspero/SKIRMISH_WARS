#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"
#include "../../types.h"

class UserPurchase : public SkirmishEvent
{
public:
	UserPurchase(Point p);
	const Point p; //el tipo vino antes!
};