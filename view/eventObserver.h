#pragma once
#include "observer.h"

#include "../Game model/FSM/GenericEvent.h"
#include "gui.h"

class eventObserver :
	public obs
{
public:
	eventObserver(GenericEvent * events, gui * g);
	~eventObserver();

	virtual void update();

private:
	GenericEvent * event;
	gui * g;
};

