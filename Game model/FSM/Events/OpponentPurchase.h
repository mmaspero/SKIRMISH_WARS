#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"
#include "../../types.h"

class OpponentPurchase : public SkirmishEvent
{
public:
	OpponentPurchase(Point p, unit_t type);
	const Point p;
	const unit_t type;
};