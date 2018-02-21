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
	
/*******************************************************************************************************
tileObserverFactory

Recibe:
Tile * t: tile de la cual se quiere obtener un tileObserver

Devuelve:
tileObserver * : -puntero al tileObserver de la tile recibida si no hay errores
				 -nullptr si ya se creo un tileObserver para la Tile recibida, si se recibe nullptr,
				 o si no se puede construir el tileObserver


********************************************************************************************************/
	tileObserver * tileObserverFactory(Tile * t);

/*******************************************************************************************************
playerObserverFactory

Recibe:
Tile * t: tile de la cual se quiere obtener un tileObserver

Devuelve:
tileObserver * : puntero al tileObserver de la tile recibida si no hay errores

nullptr si ya se creo un tileObserver para la Tile recibida, si se recibe nullptr,
o si no se puede construir el tileObserver

//TODO: hacer bien
********************************************************************************************************/
	playerObserver * playerObserverFactory(Player * p);

/*******************************************************************************************************
tileObserverFactory

Recibe:
Tile * t: tile de la cual se quiere obtener un tileObserver

Devuelve:
tileObserver * : puntero al tileObserver de la tile recibida si no hay errores

nullptr si ya se creo un tileObserver para la Tile recibida, si se recibe nullptr,
o si no se puede construir el tileObserver

//TODO: hacer bien
********************************************************************************************************/
	eventObserver * eventObserverFactory(GenericEvent * e);

	bool isValid();

/*******************************************************************************************************
tileObserverFactory

Devuelve:
ALLEGRO_DISPLAY * : puntero al display que se esta usando.

NO ENTREGA OWNERSHIP DEL DISPLAY! SI LO DESTRUIS ESTALLA TODO
********************************************************************************************************/
	ALLEGRO_DISPLAY * getDisplay();
	
/*******************************************************************************************************
getButton

Recibe:
unsigned int xPixel, yPixel: coordenadas en pixeles del punto donde se busca un boton

Devuelve:
button * : -puntero al button que se encuentra ahi si es que hay alguno
		   -nullptr si no hay un boton en ese punto

Tiene undefined behaviour si hay contentBoxs o buttons superpuestos
********************************************************************************************************/
	button * getButton(unsigned int xPixel, unsigned int yPixel);
	contentBox * getDisplaySection(unsigned int xPixel, unsigned int yPixel);

/*******************************************************************************************************
draw

Dibuja todas las secciones del display.
Si hubo un cambio de tamanio del display, se debe llamar primero a acknowledgeResize() para que 
se dibujen todos los elementos con las dimensiones correctas
//TODO: hacer private?
********************************************************************************************************/
	void draw();

/*******************************************************************************************************
acknowledgeResize

Actualiza las dimensiones de todos los elementos del display a las dimensiones actuales del display.
********************************************************************************************************/
	void acknowledgeResize();	//TODO: haver privda

	//void selectUnit(unit_t unit);	//TODO: sacar, es de debug

private:
	std::list<contentBox *> displaySections;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_MENU * menu;
	float h;
	float w;
	bool valid; 
};

/*
EVENTOS MALU MATI::::::::
-EV_DISPLAY_RESIZE
-win/lose (Enhorabuena!)
-EV_HOVER
-press / release
-tiempo que queda



*/