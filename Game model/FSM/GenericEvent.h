#pragma once
#include "eventList.h"


class GenericEvent
{
public:
	GenericEvent(event_t type);
	event_t getType();

protected:
	const event_t type;
};