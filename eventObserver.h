#pragma once
#include "observer.h"

#include "genericEvent.h"

class eventObserver :
	public observer
{
public:
	eventObserver(genericEvent * event);
	~eventObserver();

	virtual void update();
};

