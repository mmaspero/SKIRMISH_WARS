#include "network.h"
#include <stdlib.h> 
#define MIN_WAIT_CONECTION_MS 2000
#define MAX_WAIT_CONECTION_MS 3000

network::network(ip ipNumber, port portNumber)
{
	this->portNumber = portNumber;
	this->ipNumber = ipNumber;
	this->currentState = IN_CONECTION_STAGE_CLIENT;
	this->imclient = true;
	this->server = NULL;
	client = new cliente();
	srand(time(NULL));
	timer.setNewTime((rand() % MAX_WAIT_CONECTION_MS) + MIN_WAIT_CONECTION_MS);
}

void network::tryToConect()
{
	if (timer.timeOut())
	{
		if (currentState == IN_CONECTION_STAGE_CLIENT)//hago toggle de estados
		{
			delete client;
			client = NULL;
			currentState = IN_CONECTION_STAGE_SERVER;
			server = new servidor(portNumber.getPortAsInt());
		}
		else if (currentState == IN_CONECTION_STAGE_SERVER)
		{
			delete server;
			server = NULL;
			currentState = IN_CONECTION_STAGE_CLIENT;
			client = new cliente();
		}
		timer.setNewTime((rand() % MAX_WAIT_CONECTION_MS) + MIN_WAIT_CONECTION_MS);

	}

	switch (currentState)//se intenta lograr la coneccion 
	{
	case IN_CONECTION_STAGE_CLIENT://se intenta lograr la coneccion como cliente

		if (client->ConectToServer(ipNumber.getIp().c_str(), portNumber.getPortAsString().c_str()))
		{
			imclient = true;
			currentState = CONNECTED;
		}



		break;
	case IN_CONECTION_STAGE_SERVER://se intenta lograr la coneccion como servidor

		if (server->ClientIsConected())//alguien se conecto al servidor
		{
			imclient = false;
			currentState = CONNECTED;
		}

		break;
	default:
		break;

	}

}

int network::reciveData(char * buffer, int bufferSize)
{
	int sizeReciveData = 0;
	if (imclient && (client != NULL) && (currentState != _ERROR))
	{
		sizeReciveData = (client->nonBlockinReceiveDataForServer(buffer, bufferSize));
		if (sizeReciveData == MY_ERROR)
		{
			currentState = _ERROR;
			sizeReciveData = MY_ERROR;
		}
	}
	else if ((!imclient) && (server != NULL) && (currentState != _ERROR))
	{
		sizeReciveData = (server->nonBlockinReceiveDataForCliente(buffer, bufferSize));
		if (sizeReciveData == MY_ERROR)
		{
			currentState = _ERROR;
			sizeReciveData = MY_ERROR;
		}
	}
	else
	{
		currentState = _ERROR;
		sizeReciveData = MY_ERROR;
	}
	return sizeReciveData;
}

bool network::sendData(char * dataToSend, int sizeDataToSend)
{
	bool NoHuboError = false;
	if (imclient && (client != NULL) && (currentState != _ERROR))
	{
		if (!(client->sendData(dataToSend, sizeDataToSend)))
		{
			currentState = _ERROR;//hubo un error en la comunicacion
			NoHuboError = false;
		}
		else
		{
			NoHuboError = true;
		}
	}
	else if ((!imclient) && (server != NULL) && (currentState != _ERROR))
	{
		if (!(server->sendData(dataToSend, sizeDataToSend)))
		{
			currentState = _ERROR;//hubo un error en la comunicacion
			NoHuboError = false;
		}
		else
		{
			NoHuboError = true;
		}
	}
	else
	{
		currentState = _ERROR;//hubo un error en la comunicacion
		NoHuboError = false;
	}

	return NoHuboError;
}

network::~network()
{
	int i = 0;

}