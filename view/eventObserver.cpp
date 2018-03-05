#include "eventObserver.h"

#include <iostream>
#include "events/buttonHover.h"

using namespace std;

eventObserver::eventObserver(GenericEvent * event, gui * g)
{
	this->event = event; this->g = g;
	if (this->event == nullptr)
	{
		cout << "Error: el genericEvent * enviado al constructor de eventObeserver es nullptr" << endl;
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
	switch (event->getType())
	{
	case EV_ERROR:
		//TODO: poner el mensaje de error en el evento EV_ERROR
		break;
	case EV_QUIT:
		//g->appendToTextlog("f");
		break;
	case EV_USER_WON:
		//g->appendToTextlog("f");
		break;
	case EV_OPPONENT_WON:
		//g->appendToTextlog("f");
		break;
	case EV_HOVER:
		((buttonHover *)event)->getButton();
		break;
	case EV_UNHOVER:
		break;
	case EV_PRESS:

		break;
	case EV_RELEASED:
		break;



	case EV_TOGGLE_SELECT:
		if()


		break;



	case EV_TIME_LEFT:
		break;
	case EV_DISPLAY_RESIZE:
		g->acknowledgeResize();
		break;
	default:
		break;
	}
}

