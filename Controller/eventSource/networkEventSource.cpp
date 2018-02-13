#include "networkEventSource.h"
#include "../package/genericPackage.h"
#include "../package/packageMaker.h"
#include "../../Game model/FSM/SkirmishEvent.h"
#define BUFF_SIZE 500


networkEventSource::networkEventSource(network * net, Model * eventValidator)
{
}

networkEventSource::~networkEventSource()
{
}

GenericEvent * networkEventSource::getEvent()
{
	genericPackage * packageRecived = NULL;
	GenericEvent * eventRecived = NULL;
	char buffer[BUFF_SIZE];
	int recivedData = 0;
	if (net->getCurrentState() == CONNECTED)
	{
		recivedData = net->reciveData(buffer, BUFF_SIZE);
		if (recivedData > 0)//llego informacion
		{

			//typedef enum events {
			//	EV_TIMEOUT, EV_ACK, EV_GO_TO_PURCHASE,
			//	EV_USER_PASS, EV_USER_ATTACK, EV_USER_MOVE, EV_USER_PURCHASE,
			//	EV_OPP_PASS, EV_OPP_ATTACK, EV_OPP_MOVE, EV_OPP_PURCHASE,	//OPP es de OPPONENT
			//	EV_PURCH_SELECTION, EV_UNIT_SELECTION, EV_UNSELECT,

			//	EV_USER_WON, EV_OPPONENT_WON,	//ESTOS NO LLEGAN A LA FSM!!
			//	N_EVENTS
			//} event_t;
			packageRecived = packageMaker(buffer, recivedData);
			if (packageRecived != NULL)//hay un paquete valido
			{
				switch (packageRecived->getType())
				{
				case ATTACK:
					eventRecived = eventValidator->validateOpponentAttack((attack *)packageRecived);
					break;
				case MOVE:
					eventRecived = eventValidator->validateOpponentMove((move *)packageRecived);
					break;
				case PURCHASE:
					eventRecived = eventValidator->validateOpponentPurchase((purchase *)packageRecived);
					break;
				case ACK:
					eventRecived = new SkirmishEvent(EV_ACK);
					break;
				default:

					break;
				}

				if (eventRecived != NULL)
				{
					return eventRecived;
				}

			}

			else if (recivedData = 0)//no llego data
			{
				return NULL;
			}

			
		}
		
	}
	return new SkirmishEvent(EV_ERROR);
}