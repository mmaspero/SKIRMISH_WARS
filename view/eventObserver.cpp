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
#include "simpleButton.h"
#include "gui.h"

//TODO: hacer unos mensajes un poco mas prolijos
#define YOU_WON_MSG "Ganaste kpo"
#define OPPONENT_WON_MSG "Perdiste loser"
#define ERROR_MSG "Hubo un error"
#define QUIT_MSG "El oponente se fue del juego"

#define YOU_PASS_MSG "Pasaste tu turno"
#define THEY_PASS_MSG "Es tu turno"

#define TIMEOUT_MSG "Timeout"


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
	if ((*event) != nullptr)
	{
		switch ((*event)->getType())
		{
		case EV_TIMEOUT:
			break;
		case EV_ACK:
			break;
		case EV_GO_TO_PURCHASE:
			break;
		case EV_USER_PASS:
			break;
		case EV_USER_ATTACK:
			break;
		case EV_USER_MOVE:
			break;
		case EV_USER_PURCHASE:
			break;
		case EV_OPP_PASS:
			onOppPass();
			break;
		case EV_OPP_ATTACK:
			break;
		case EV_OPP_MOVE:
			break;
		case EV_OPP_PURCHASE:
			break;
		case EV_PURCH_SELECTION:
			break;
		case EV_UNIT_SELECTION:
			break;
		case EV_UNSELECT:
			break;
		case EV_WAIT_FOR_YOU_WON:
			break;
		case EV_YOU_WON:
			break;
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
}

void eventObserver::onTimeout()
{
	g->appendToTextlog(TIMEOUT_MSG);
	g->changeToolboxTurn();
}

void eventObserver::onOppPass()
{
	((toolbox*)(g->getDisplaySection(TOOLBOX)))->goToMyTurn();
	((toolbox*)(g->getDisplaySection(TOOLBOX)))->draw();
	g->appendToTextlog(THEY_PASS_MSG);
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
	((buttonHover *)(*event))->getButton()->hoveredOn();
}

void eventObserver::onButtonUnhover()
{
	((buttonUnhover *)(*event))->getButton()->hoveredOff();
}

void eventObserver::onButtonPress()
{
	((buttonPress *)(*event))->getButton()->pressedOn();
}

void eventObserver::onButtonRelease()
{
	((buttonRelease *)(*event))->getButton()->pressedOff();	//TODO: arreglar

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
			toolboxP->draw();
		}
		g->getDisplaySection(TOOLBOX)->draw();
	}
	else if (b->getType() == SIMPLE_BUTTON)
	{
		switch (((simpleButton *)b)->getSimpleType())
		{
		case CANCEL_BUTTON:
			break;
		case BUY_BUTTON: case BACK_BUTTON:
			if (g->getToolbox()->getStatus() == SHOWING_ONE_PRODUCT)
			{
				g->getToolbox()->goToStore();
			}
			break;
		case STORE_BUTTON:
			if (g->getToolbox()->getStatus() == EMPTY_MY_TURN || g->getToolbox()->getStatus() == SHOWING_UNIT_INFO)
			{
				g->getToolbox()->goToStore();
			}
			break;
		case PASS_BUTTON:
			g->getToolbox()->goToTheirTurn();
			g->appendToTextlog(YOU_PASS_MSG);
			break;
		default:
			break;
		}
		g->getDisplaySection(TOOLBOX)->draw();
	}
	else
	{
		b->selectedOn();
	}
}

void eventObserver::onButtonSelect()
{
	//TODO: hacer menos cabeza
}

void eventObserver::onButtonUnselect()
{

	button * b = ((buttonUnselect *)(*event))->getButton();	//TODO: control de error
	if (b->getType() != PRODUCT_BUTTON)
	{
		b->selectedOff();
	}
}

void eventObserver::onTimeLeft()
{
	g->setTimeLeft(((timeLeft *)(*event))->getTime());

}

void eventObserver::onDisplayResize()
{
	g->acknowledgeResize();
}

