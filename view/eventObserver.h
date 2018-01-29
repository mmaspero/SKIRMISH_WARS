#pragma once
#include "observer.h"

#include "genericEvent.h"
#include "gui.h"

class eventObserver :
	public observer
{
public:
	eventObserver(genericEvent * events);
	~eventObserver();

	virtual void update();
private:
	genericEvent * events;
};

