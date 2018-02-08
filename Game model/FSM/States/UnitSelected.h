#pragma once
#include "../GenericState.h"
#include "../../../Point.h"

class UnitSelected : public GenericState {
public:
	UnitSelected(Point selection);

	GenericState * onTimeout(GenericEvent *);
	GenericState * onUserPass(GenericEvent *);
	GenericState * onUserAttack(GenericEvent *);
	GenericState * onUserMove(GenericEvent *);
	GenericState * onGoToPurchase(GenericEvent *);
	GenericState * onUnitSelection(GenericEvent *);
	GenericState * onPurchaseSelection(GenericEvent *);
	GenericState * onUnselect(GenericEvent *);

protected:
	const Point selection;
};
