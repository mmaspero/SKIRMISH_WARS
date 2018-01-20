#ifndef GenericState_h
#define GenericState_h

#include <cstdio>
#include "GenericEvent.h"



class GenericState
{
public:
#if I_AM == CLIENT
	virtual GenericState* onMakeRrq		(GenericEvent *);
    virtual GenericState* onMakeWrq		(GenericEvent *);
#else
	virtual GenericState* onRrq			(GenericEvent *);
    virtual GenericState* onWrq			(GenericEvent *);
#endif
    virtual GenericState * onData (GenericEvent *);
    virtual GenericState * onLastData (GenericEvent *);
    virtual GenericState * onAck (GenericEvent *);
    virtual GenericState * onTimeout (GenericEvent *);
    virtual GenericState * onError (GenericEvent *);
	virtual GenericState * onLastPaqSent (GenericEvent *);
};


#endif /* GenericState_h */

