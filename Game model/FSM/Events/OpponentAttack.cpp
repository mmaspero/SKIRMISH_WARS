#include "OpponentAttack.h"

OpponentAttack::OpponentAttack(Point attacker, Point target, unsigned int dice) : SkirmishEvent(EV_OPP_ATTACK), 
																attacker(attacker), target(target), dice(dice)
{
	;
}
