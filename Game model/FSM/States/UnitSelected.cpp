#include "UnitSelected.h"
#include "OpponentMoving.h"
#include "UserMoving.h"
#include "UserPurchasing.h"
#include "UserAttacking.h"
#include "WaitingMoveAck.h"
#include "skirmishHandlers.h"
#include "../Events/UserAttack.h"
#include "../Events/UserMove.h"
#include "../Events/UnitSelection.h"

UnitSelected::UnitSelected(Point selection) : GenericState(UNIT_SELECTED), selection(selection)
{
	;
}

GenericState * UnitSelected::onTimeout(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UnitSelected::onUserPass(GenericEvent *e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new OpponentMoving();
}

GenericState * UnitSelected::onUserAttack(GenericEvent *e)
{
	UserAttack * ev = (UserAttack *)e;
	unsigned int die = rand() % 6 + 1;
	ev->model()->registerAttack(selection, ev->target, die);
	ev->contr()->sendAttack(die, selection.row, selection.col, ev->target.row, ev->target.col);
	//ev->contr()->resetPlayTimer;
	return new UserAttacking(selection, ev->target);
}

GenericState * UnitSelected::onUserMove(GenericEvent * e)
{
	UserMove * ev = (UserMove *)e;
	ev->model()->registerMove(selection, ev->pf);
	ev->contr()->sendMove(selection.row, selection.col, ev->pf.row, ev->pf.col);
	//ev->contr()->resetPlayTimer();
	return new WaitingMoveAck();
}

GenericState * UnitSelected::onGoToPurchase(GenericEvent * ev)
{
	((SkirmishEvent*)ev)->model()->clearActions();
	return new UserPurchasing();
}

GenericState * UnitSelected::onUnitSelection(GenericEvent *e)
{
	UnitSelection * ev = (UnitSelection*)e;
	ev->model()->clearActions();
	return new UnitSelected(ev->tile);
}

GenericState * UnitSelected::onPurchaseSelection(GenericEvent * ev)
{
	((SkirmishEvent*)ev)->model()->clearActions();
	return new UserMoving(); //lo tomo como un unselect
}

GenericState * UnitSelected::onUnselect(GenericEvent * ev)
{
	((SkirmishEvent*)ev)->model()->clearActions();
	return new UserMoving();
}
