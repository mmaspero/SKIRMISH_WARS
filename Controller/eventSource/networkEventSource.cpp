#include "networkEventSource.h"
#include "../package/genericPackage.h"
#include "../package/packageMaker.h"
#include "../../Game model/FSM/SkirmishEvent.h"
#define BUFF_SIZE 500


networkEventSource::networkEventSource(network * net, Model * eventValidator)
{
	this->net = net;
	this->eventValidator = eventValidator;

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
				case PASS:
					eventRecived = new SkirmishEvent(EV_OPP_PASS);
					break;
				default:

					break;
				}

				if (eventRecived != NULL)
				{
					return eventRecived;
				}

			}
			
		}
		else if (recivedData == 0)//no llego data
		{
			return NULL;
		}
		
	}
	return new SkirmishEvent(EV_ERROR);
}