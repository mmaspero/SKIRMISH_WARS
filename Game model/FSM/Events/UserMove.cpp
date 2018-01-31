#include "UserMove.h"

UserMove::UserMove(Point p0, Point pf) : SkirmishEvent(EV_USER_MOVE), p0(p0), pf(pf)
{
	;
}
