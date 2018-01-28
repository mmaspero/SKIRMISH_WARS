#ifndef GenericState_h
#define GenericState_h

#include <cstdio>
#include "GenericEvent.h"



class GenericState
{
public:
	GenericState(state_t id);
	
	state_t name() const;

	virtual GenericState * onTimeout (GenericEvent *);
	virtual GenericState * onAck (GenericEvent *);
	virtual GenericState * onUserPass (GenericEvent *);
	virtual GenericState * onUserAttack (GenericEvent *);
	virtual GenericState * onUserMove (GenericEvent *);
	virtual GenericState * onUserPurchase (GenericEvent *);
	virtual GenericState * onGoToPurchase(GenericEvent *);
	virtual GenericState * onOpponentPass(GenericEvent *);
	virtual GenericState * onOpponentAttack(GenericEvent *);
	virtual GenericState * onOpponentMove(GenericEvent *);
	virtual GenericState * onOpponentPurchase(GenericEvent *);
	virtual GenericState * onPurchaseSelection(GenericEvent *);
	virtual GenericState * onUnitSelection(GenericEvent *);
	virtual GenericState * onUnselect(GenericEvent *);

private:
	const state_t id;
};


#endif /* GenericState_h */

