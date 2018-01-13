#pragma once

#include "contentBox.h"
#include "Board.h"
#include "Tile.h"

#include "tileObserver.h"
#include "playerObserver.h"



enum {BOARD, SCOREBOARD, TEXTLOG, TOOLBOX, OPTIONS, DISPLAY_SECTION_N};

class gui
{
public:
	gui();
	~gui();
	
	tileObserver * tileObserverFactory(Tile * t);
	playerObserver * playerObserverFactory(Player * p);

private:
	contentBox * displaySections[DISPLAY_SECTION_N];
	ALLEGRO_DISPLAY * display;
	float h;
	float w;

	bool valid; 
};

