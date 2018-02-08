#pragma once
#include "../GenericState.h"
#include "../../../Point.h"

class UserAttacking : public GenericState {
public:
	UserAttacking(Point user, Point opponent);

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onOpponentAttack(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);

	bool isWaitingFor(Point p0, Point pf) const;
protected:
	const Point user, opponent;
};