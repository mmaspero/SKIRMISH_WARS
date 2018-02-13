#pragma once
#include "eventSource.h"
#include "../network/network.h"
#include "../../Game model/FSM/GenericEvent.h"
#include "../../Game model/Model.h"

class networkEventSource: public eventSource
{
public:
	networkEventSource(network * net, Model * eventValidator);
	~networkEventSource();
	
	//getEvent(), devuelve si hubo algun evento de red, si devuelve NULL no hubo evento
	GenericEvent * getEvent();

private:
	network * net;
	Model * eventValidator;

};
