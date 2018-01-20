#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

#ifndef I_AM

#define	CLIENT	1	
#define SERVER	0

#define I_AM SERVER
#endif // !I_AM


#if I_AM == CLIENT
typedef enum{EV_ACK, EV_DATA, EV_LAST_DATA, EV_TIMEOUT, EV_ERROR, EV_EXIT, EV_HELP, 
			EV_MAKE_RRQ, EV_MAKE_WRQ, EV_LAST_PAQ_SENT, EVENT_COUNT} event_t;
#elif I_AM == SERVER
typedef enum{EV_ACK, EV_DATA, EV_LAST_DATA, EV_TIMEOUT, EV_ERROR, EV_EXIT, EV_HELP, 
			EV_RRQ, EV_WRQ, EV_LAST_PAQ_SENT, EVENT_COUNT} event_t;
#else
#error	"This program must emulate either a CLIENT or a SERVER in a TFTP connection"
#endif

#include "EventsInfo.h"

class EventsInfo;

class GenericEvent
{
public:
	void setEvInfo(EventsInfo * i);
	event_t getType();
	EventsInfo * i;

protected:
	event_t type;
};


#endif //GENERIC_EVENT_H