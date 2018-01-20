#include "GenericState.h"

#if I_AM == CLIENT

GenericState* GenericState :: onMakeRrq (GenericEvent * ev)
{
    return NULL;
}

GenericState* GenericState :: onMakeWrq (GenericEvent * ev)
{
    return NULL;
}


#else
GenericState * GenericState :: onRrq (GenericEvent * ev)
{
    return NULL;
}

GenericState * GenericState :: onWrq (GenericEvent * ev)
{
    return NULL;
}
#endif

GenericState * GenericState :: onData (GenericEvent * ev)
{
    return NULL;
}


GenericState * GenericState :: onLastData (GenericEvent * ev)
{
    return NULL;
}


GenericState * GenericState :: onAck(GenericEvent * ev)
{
    return NULL;
}

GenericState* GenericState :: onLastPaqSent (GenericEvent * ev)
{
    return NULL;
}

GenericState * GenericState :: onTimeout(GenericEvent * ev)
{
    return NULL;
}

GenericState * GenericState :: onError (GenericEvent * ev)
{
    return NULL;
}
