#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"
#include "../../types.h"

class UserPurchase : public SkirmishEvent
{
public:
	UserPurchase(Point p, unit_t type);
	const Point p;
	const unit_t type;
};