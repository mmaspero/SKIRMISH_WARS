#pragma once
#include "UserAttacking.h"

class WaitingAttackTurnOver : public UserAttacking {
public:
	WaitingAttackTurnOver(Point user, Point opponent);

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);
	GenericState * onOpponentAttack(GenericEvent *);
	GenericState * onWaitForYouWon(GenericEvent *);
};