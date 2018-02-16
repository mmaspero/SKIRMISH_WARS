#include "eventGenerator.h"

eventGenerator::eventGenerator()
{
}

eventGenerator::~eventGenerator()
{
}

void eventGenerator::addEventSource(eventSource * evSource)
{
	eventSources.push_back(evSource);
}

GenericEvent * eventGenerator::getNextEvent()
{
	GenericEvent * nextEvent = NULL;
	if (!eventQueue.empty())
	{
		nextEvent = eventQueue.front();
		eventQueue.pop_front();

	}
	return nextEvent;
}

void eventGenerator::updateEventQueue()
{
	GenericEvent * arrivedEvent = NULL;
	for (std::vector<eventSource *>::iterator i = eventSources.begin(); i != eventSources.end(); i++)
	{
		arrivedEvent = (*i)->getEvent();
		if (arrivedEvent != NULL)
		{
			eventQueue.push_back(arrivedEvent);
		}
	}
}
