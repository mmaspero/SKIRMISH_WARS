#pragma once

#include "contentBox.h"
#include "Board.h"
#include "../Game model/Tile.h"
#include "../Game model/FSM/GenericEvent.h"

#include "tileObserver.h"
#include "playerObserver.h"
#include "eventObserver.h"

#include "button.h"

#include <allegro5\allegro_native_dialog.h>


class tileObserver;
class playerObserver;
class eventObserver;
class Player;
class Tile;

//TODO: ponerle types a los botones

class gui
{
public:
	gui();
	~gui();
	
	tileObserver * tileObserverFactory(Tile * t);
	playerObserver * playerObserverFactory(Player * p);
	eventObserver * eventObserverFactory(GenericEvent * e);

	bool isValid();

	//getDisplay:
	//devuelve un puntero al display sin entregar ownership
	ALLEGRO_DISPLAY * getDisplay();

	button * getButton(unsigned int xPixel, unsigned int yPixel);
	contentBox * getDisplaySection(unsigned int xPixel, unsigned int yPixel);

	void draw();

	//acknowledgeResize:
	//actualiza las dimensiones de todas las displaySections a las dimensiones actuales del display.
	void acknowledgeResize();

private:
	std::list<contentBox *> displaySections;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_MENU * menu;
	float h;
	float w;
	bool valid; 
};

