#include "UserAttack.h"

UserAttack::UserAttack(Point attacker, Point target)  : SkirmishEvent(EV_USER_ATTACK), attacker(attacker), target(target)
{
	;
}
