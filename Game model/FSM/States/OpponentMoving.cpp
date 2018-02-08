#include "skirmishHandlers.h"
#include "OpponentMoving.h"
#include "OpponentPurchasing.h"
#include "WaitingOpponentPass.h"
#include "UserMoving.h"
#include "../Events/OpponentMove.h"
#include "../Events/OpponentAttack.h"
#include "../Events/OpponentPurchase.h"

OpponentMoving::OpponentMoving() : GenericState(OPP_MOVING)
{
	;
}

GenericState * OpponentMoving::onTimeout(GenericEvent * e)
{
	//SkirmishEvent * ev = (SkirmishEvent *)e;
	//ev->contr()->stopPlayTimer(); ?
	return new WaitingOpponentPass();
}

GenericState * OpponentMoving::onUserPass(GenericEvent *)
{
	return this; // nada!!!!!!!!!!!!!!!!!!!!!!!!!
}

GenericState * OpponentMoving::onGoToPurchase(GenericEvent *)
{
	return this; // nada!!!!!!!!!!!!!!!!!!!!!!!!!
}

GenericState * OpponentMoving::onOpponentPass(GenericEvent * e)
{
	skirmishHandler::nextTurn((SkirmishEvent *)e);
	return new UserMoving();
}

GenericState * OpponentMoving::onOpponentAttack(GenericEvent * e)
{
	OpponentAttack * ev = (OpponentAttack *)e;
	unsigned int dice = ev->dice;
	ev->model()->registerAttack(ev->attacker, ev->target, dice);
	dice = rand() % 6 + 1;
	ev->model()->registerAttack(ev->target, ev->attacker, dice);
	//ev->contr()->resetPlayTimer();
//	ev->contr()->sendAttack(dice, ev->target.row, ev->target.col, ev->attacker.row, ev->attacker.col);
	ev->model()->endAttack(ev->attacker);
	return this;
}

GenericState * OpponentMoving::onOpponentMove(GenericEvent * e)
{
	OpponentMove * ev = (OpponentMove *)e;
	ev->model()->registerMove(ev->p0, ev->pf);
	//ev->contr()->resetPlayTimer();
	//ev->contr()->sendOneBytePackage(ACK);
	return this;
}

GenericState * OpponentMoving::onOpponentPurchase(GenericEvent * e)
{
	OpponentPurchase * ev = (OpponentPurchase *)e;
	ev->model()->registerPurchase(OPPONENT, ev->p, ev->type);
	//ev->contr()->resetPlayTimer();
	//ev->contr()->sendOneBytePackage(ACK);
	return new OpponentPurchasing();
}

GenericState * OpponentMoving::onPurchaseSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onUnitSelection(GenericEvent *)
{
	return this;
}

GenericState * OpponentMoving::onUnselect(GenericEvent *)
{
	return this;
}