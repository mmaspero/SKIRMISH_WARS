#include "GenericEvent.h"

void GenericEvent :: setEvInfo(EventsInfo * i)
{ this->i = i; }

event_t GenericEvent :: getType()
 {	return type; }