#pragma once

#include "observer.h"
#include "Tile.h"
#include "tileButton.h"
#include "toolbox.h"

class tileObserver : public observer
{
public:
	tileObserver(Tile * t, tileButton * tButton, toolbox * tBox);
	~tileObserver();
	virtual void update();
private:
	tileButton * tButton;
	toolbox * tBox;
	Tile * t;
};

