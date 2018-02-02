#include "SkirmishEvent.h"


Controller * SkirmishEvent::cont = nullptr;
Model * SkirmishEvent::mod = nullptr;


SkirmishEvent::SkirmishEvent(event_t type) : GenericEvent(type)
{
	;
}

void SkirmishEvent::setModel(Model * mod)
{
	if (SkirmishEvent::mod == nullptr)
		SkirmishEvent::mod = mod;
}

void SkirmishEvent::setController(Controller * cont)
{
	if (SkirmishEvent::cont == nullptr) {
		SkirmishEvent::cont = cont;
	}
}

Model * SkirmishEvent::model()
{
	return mod;
}

Controller * SkirmishEvent::contr()
{
	return cont;
}
