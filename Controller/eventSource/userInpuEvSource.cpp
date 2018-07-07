#include "userInpuEvSource.h"
#include <iostream>
#include"../../view/button.h"
#include"../../view/tileButton.h"
#include"../../Game model/FSM/SkirmishEvent.h"
#include"../../Game model/FSM/FsmInfo.h"
#include "../../view/simpleButton.h"



userInputEvSource::userInputEvSource(ALLEGRO_DISPLAY * window, gui * usserInterface, Model * packageValidator)
{
	this->setType(MAUSE_KEYBOARD);
	this->window = window;
	this->usserInterface = usserInterface;
	this->packageValidator = packageValidator;
	eventQueue = al_create_event_queue();
	if (eventQueue)
	{
		if (al_install_keyboard())
		{
			if (al_install_mouse())
			{
				al_register_event_source(eventQueue, al_get_display_event_source(this->window));
				//al_register_event_source(eventQueue, al_get_keyboard_event_source()); // no se usa el teclado
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
	button * buttonSelected = nullptr;
	GenericEvent * recivedEvent = NULL;

	if (al_get_next_event(eventQueue, &(this->event)))
	{
		switch (event.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP://se solto una tecla del mause
			buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
			if (buttonSelected != nullptr)
			{
				if (buttonSelected->getType() == TILE_BUTTON)
				{
					recivedEvent = packageValidator->getTileEvent(((tileButton*)buttonSelected)->getTilePosition());
					return recivedEvent;
				}
				else if (buttonSelected->getType() == SIMPLE_BUTTON && ((simpleButton*)buttonSelected)->isItPass()) {
					return new SkirmishEvent(EV_USER_PASS);
				}
			}
			else//no se preciono nada valido
			{
				return NULL;
			}
			//eventos de realease
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
			//aca evento de press
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
			//aca eventos de hover
			break;
			

		default:
			return NULL;
			break;
		}


	}
	
	
		return NULL;

	
}
