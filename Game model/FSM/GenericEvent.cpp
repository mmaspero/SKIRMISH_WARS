#include "GenericEvent.h"

GenericEvent::GenericEvent(event_t type) : type(type)
{
	;
}

event_t GenericEvent :: getType()
 {	
	return type;
}