#include "userInpuEvSource.h"
#include <iostream>


userInputEvSource::userInputEvSource(ALLEGRO_DISPLAY * window)
{
	this->setType(MAUSE_KEYBOARD);
	this->window = window;
	eventQueue = al_create_event_queue();
	if (eventQueue)
	{
		if (al_install_keyboard())
		{
			if (al_install_mouse())
			{
				al_register_event_source(eventQueue, al_get_display_event_source(this->window));
				al_register_event_source(eventQueue, al_get_keyboard_event_source());
				al_register_event_source(eventQueue, al_get_mouse_event_source());
			}
			else
			{
				al_destroy_event_queue(eventQueue);
				failToInit = true;
			}
			
		}
		else
		{
			al_destroy_event_queue(eventQueue);
			failToInit = true;
		}
		
	}
	else
	{
		failToInit = true;
	}
	
	
	


}

userInputEvSource::~userInputEvSource()
{
	if (!failToInit)
	{
		al_destroy_event_queue(eventQueue);
	}
	
}

GenericEvent * userInputEvSource::getEvent()
{

	
	if (al_get_next_event(eventQueue, &(this->event)))
	{


	}
	else
	{
		return NULL;
	}
	
}
