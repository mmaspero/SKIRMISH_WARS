#include "userInpuEvSource.h"
#include <iostream>
#include"../../view/button.h"
#include"../../view/tileButton.h"
#include"../../Game model/FSM/SkirmishEvent.h"
#include"../../Game model/FSM/FsmInfo.h"
#include "../../view/simpleButton.h"
#include "../../view/events/buttonRelease.h"
#include "../../view/events/buttonHover.h"
#include "../../view/events/buttonPress.h"
#include "../../view/events/buttonSelect.h"
#include "../../view/events/buttonUnhover.h"
#include "../../view/events/buttonUnselect.h"
#include "../../view/events/displayResize.h"
#include "../../view/events/timeLeft.h"




userInputEvSource::userInputEvSource(ALLEGRO_DISPLAY * window, gui * usserInterface, Model * packageValidator)
{
	this->setType(MAUSE_KEYBOARD);
	this->window = window;
	this->usserInterface = usserInterface;
	this->packageValidator = packageValidator;
	this->eventToSend = NULL;
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
	if (this->eventToSend != NULL)
	{

		recivedEvent = this->eventToSend;
		this->eventToSend = NULL;
		return recivedEvent;
	}
	if (al_get_next_event(eventQueue, &(this->event)))
	{
		buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
		switch (event.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP://se solto una tecla del mouse
			//buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
			if (buttonSelected != nullptr)
			{
				this->eventToSend = new buttonRelease(buttonSelected);

				if (buttonSelected->getType() == TILE_BUTTON)
				{
					recivedEvent = packageValidator->getTileEvent(((tileButton*)buttonSelected)->getTilePosition());
					return recivedEvent;
				}
				else if (buttonSelected->getType() == SIMPLE_BUTTON) {
					simpleButtonType_t simpleType = ((simpleButton*)buttonSelected)->getSimpleType();
					switch (simpleType)
					{
					case PASS_BUTTON:
						return new SkirmishEvent(EV_USER_PASS);
						break;
					case STORE_BUTTON:
						return new SkirmishEvent(EV_GO_TO_PURCHASE);
						break;
					case BUY_BUTTON:
						return new SkirmishEvent(EV_USER_PURCHASE);
						break;
					case BACK_BUTTON:
						
						break;
					case CANCEL_BUTTON:

						break;
					default:
						break;
					}
					
				}
			}
			else//no se preciono nada valido
			{
				return NULL;
			}
			/*eventos de realease*/
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (buttonSelected != nullptr)
			{
				//return new buttonPress(buttonSelected);
			}
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			//buttonSelected = usserInterface->getButton(event.mouse.x, event.mouse.y);
			//aca eventos de hover
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			return ((GenericEvent *) new displayResize);
			break;
			

		default:
			return NULL;
			break;
		}


	}
	
	
		return NULL;

	
}
