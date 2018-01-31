#include "OpponentPurchase.h"

OpponentPurchase::OpponentPurchase(Point p, unit_t type) : SkirmishEvent(EV_OPP_PURCHASE), p(p), type(type)
{
	;
}
