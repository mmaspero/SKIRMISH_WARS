#include "PurchaseSelection.h"

PurchaseSelection::PurchaseSelection(unit_t type) : SkirmishEvent(EV_PURCH_SELECTION), selection(type)
{
	;
}
