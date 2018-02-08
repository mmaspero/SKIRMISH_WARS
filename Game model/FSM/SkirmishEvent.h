#pragma once
#include "GenericEvent.h"
#include "../Model.h"
#include "../../Controller/controller.h"

class SkirmishEvent : public GenericEvent {
public:
	SkirmishEvent(event_t type);

	static void setModel(Model * mod);	//solo lo van a hacer una vez!
	static void setController(Controller * cont);

	Model * model();
	Controller * contr();

protected:
	static Model * mod;
	static Controller * cont;
};