#pragma once
#include "FsmInfo.h"


class GenericEvent
{
public:
	GenericEvent(event_t type);
	event_t getType();

protected:
	const event_t type;
};