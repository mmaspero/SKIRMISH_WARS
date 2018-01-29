#pragma once
#include "GenericEvent.h"
#include "../Model.h"

class Controller;	//eventualmente incluir controller y listo

class SkirmishEvent : public GenericEvent {
public:
	SkirmishEvent(event_t type);

	static void setModel(Model * mod);	//solo lo van a hacer una vez!
	static void setController(Controller * cont);

protected:
	static Model * mod;
	static Controller * cont;
};