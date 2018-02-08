#pragma once
#include "../SkirmishEvent.h"
#include "../../../Point.h"
#include "../../types.h"

class PurchaseSelection : public SkirmishEvent
{
public:
	PurchaseSelection(unit_t type);
	const unit_t selection;
};