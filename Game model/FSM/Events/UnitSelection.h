#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"

class UnitSelection : public SkirmishEvent
{
public:
	UnitSelection(Point tile);
	const Point tile;
};

