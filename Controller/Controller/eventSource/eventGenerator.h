#pragma once
#include"../../Game model/FSM/GenericEvent.h"
#include"eventSource.h"
#include <list>
#include<vector>
class eventGenerator
{
public:
	eventGenerator();
	~eventGenerator();

	void addEventSource(eventSource * evSource);
	/*getNextEvent devuelve el proximo evento en la cola de eventos, si no hay devuelve
	NULL*/
	GenericEvent * getNextEvent();
	void updateEventQueue();
	std::list<GenericEvent *> eventQueue;
private:
	std::vector<eventSource *> eventSources;
	


};
