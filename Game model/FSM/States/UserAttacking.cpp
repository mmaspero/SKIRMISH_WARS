#include "UserAttacking.h"
#include "WaitingAttackTurnOver.h"
#include "UserMoving.h"
#include "WaitingYouWon.h"
#include "../Events/OpponentAttack.h"

UserAttacking::UserAttacking(Point user, Point opponent) : GenericState(USER_ATTACKING), user(user), opponent(opponent)
{
	;
}

GenericState * UserAttacking::onTimeout(GenericEvent *)
{
	return new WaitingAttackTurnOver(user, opponent);
}

GenericState * UserAttacking::onUserPass(GenericEvent *)
{
	return new WaitingAttackTurnOver(user, opponent);
}

GenericState * UserAttacking::onOpponentAttack(GenericEvent * e)
{
	OpponentAttack * ev = (OpponentAttack *)e;
	ev->model()->registerAttack(ev->attacker, ev->target, ev->dice);
	ev->contr()->resetPlayTimer();
	ev->model()->endAttack(opponent);
	return new UserMoving();
}

GenericState * UserAttacking::onGoToPurchase(GenericEvent *)
{
	return this;
}

GenericState * UserAttacking::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * UserAttacking::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * UserAttacking::onUnselect(GenericEvent *)
{
	return this;
}

GenericState * UserAttacking::onWaitForYouWon(GenericEvent * ev)
{
	((SkirmishEvent*)ev)->model()->endAttack(opponent);

	return new WaitingYouWon();
}

bool UserAttacking::isWaitingFor(Point p0, Point pf) const
{
	return (p0 == opponent && pf == user);
}
