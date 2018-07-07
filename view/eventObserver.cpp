#include "eventObserver.h"

#include <iostream>
#include "events/buttonHover.h"
#include "events/buttonPress.h"
#include "events/buttonRelease.h"
#include "events/buttonSelect.h"
#include "events/buttonUnhover.h"
#include "events/buttonUnselect.h"
#include "events/timeLeft.h"

#include "productButton.h"
#include "textlog.h"

#include "gui.h"

//TODO: hacer unos mensajes un poco mas prolijos
#define YOU_WON_MSG "Ganaste kpo"
#define OPPONENT_WON_MSG "Perdiste loser"
#define ERROR_MSG "Hubo un error"
#define QUIT_MSG "El oponente se fue del juego"


using namespace std;

eventObserver::eventObserver(GenericEvent ** event, gui * g)
{
	this->event = event; 
	this->g = g;
	if (this->event == nullptr)
	{
		cout << "Error: el genericEvent ** enviado al constructor de eventObserver es nullptr" << endl;
		valid = false;
	}	
	if (this->g == nullptr)
	{
		cout << "Error: el gui * enviado al constructor de eventObeserver es nullptr" << endl;
		valid = false;
	}
	else
	{
		valid = true;
	}
}

eventObserver::~eventObserver()
{
}

void eventObserver::update()
{
	switch ((*event)->getType())
	{
	case EV_ERROR:
		onError();
		break;
	case EV_QUIT:
		onQuit();
		break;
	case EV_USER_WON:
		onUserWon();
		break;
	case EV_OPPONENT_WON:
		onOpponentWon();
		break;
	case EV_BUTTON_HOVER:
		onButtonHover();
		break;
	case EV_BUTTON_UNHOVER:
		onButtonUnhover();
		break;
	case EV_BUTTON_PRESS:
		onButtonPress();
		break;
	case EV_BUTTON_RELEASE:
		onButtonRelease();
		break;
	case EV_BUTTON_SELECT:
		onButtonSelect();
		break;
	case EV_BUTTON_UNSELECT:
		onButtonSelect();
		break;
	case EV_TIME_LEFT:
		onTimeLeft();
		break;
	case EV_DISPLAY_RESIZE:
		onDisplayResize();
		break;
	default:
		//TODO:
		break;
	}
}

void eventObserver::onError()
{
	g->appendToTextlog(ERROR_MSG);
}

void eventObserver::onQuit()
{
	g->appendToTextlog(QUIT_MSG);
}

void eventObserver::onUserWon()
{
	g->appendToTextlog(YOU_WON_MSG);
}

void eventObserver::onOpponentWon()
{
	g->appendToTextlog(OPPONENT_WON_MSG);
}

void eventObserver::onButtonHover()
{
	g->appendToTextlog("Llego evento button hover");	//TODO: sacar de debug
	((buttonHover *)(*event))->getButton()->hoveredOn();
}

void eventObserver::onButtonUnhover()
{
	g->appendToTextlog("Llego evento button unhover");	//TODO: sacar de debug
	((buttonUnhover *)(*event))->getButton()->hoveredOff();
}

void eventObserver::onButtonPress()
{
	g->appendToTextlog("Llego evento button press");	//TODO: sacar de debug
	((buttonPress *)(*event))->getButton()->pressedOn();
}

void eventObserver::onButtonRelease()
{
	g->appendToTextlog("Llego evento button RELEASE");	//TODO: sacar de debug
	((buttonRelease *)(*event))->getButton()->pressedOff();
}

void eventObserver::onButtonSelect()
{
	//TODO: hacer menos cabeza
	g->appendToTextlog("Llego evento button select");	//TODO: sacar de debug

	button * b = ((buttonSelect *)(*event))->getButton();	//TODO: control de error

	if (b->getType() == PRODUCT_BUTTON)
	{
		toolbox * toolboxP = ((toolbox *)g->getDisplaySection(TOOLBOX));
		if (toolboxP == nullptr)
		{
			cout << "Error, no se pudo encontrar el displaySection toolbox" << endl;
		}
		else
		{
			toolboxP->selectProduct(((productButton *)b)->getUnitSpecificType());
		}
	}
	else
	{
		b->selectedOn();
	}
}

void eventObserver::onButtonUnselect()
{
	g->appendToTextlog("Llego evento button unselect");	//TODO: sacar de debug

	button * b = ((buttonUnselect *)(*event))->getButton();	//TODO: control de error
	if (b->getType() != PRODUCT_BUTTON)
	{
		b->selectedOff();
	}
}

void eventObserver::onTimeLeft()
{
	g->appendToTextlog("Llego evento button time left");	//TODO: sacar de debug
	g->setTimeLeft(((timeLeft *)(*event))->getTime());
}

void eventObserver::onDisplayResize()
{
	g->appendToTextlog("Llego evento button hover");	//TODO: sacar de debug
	g->acknowledgeResize();
}
