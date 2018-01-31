#include "UserPurchase.h"

UserPurchase::UserPurchase(Point p, unit_t type) : SkirmishEvent(EV_USER_PURCHASE), p(p), type(type)
{
	;
}
