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

class gui
{
public:

	friend class eventObserver;

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
	Player * p: player del cual se quiere obtener un playerObserver

	Devuelve:
	playerObserver * : puntero al playerObserver del player recibido si no hay errores

	//TODO: que devuelva nullptr si ese player ya tiene observer
	********************************************************************************************************/
	playerObserver * playerObserverFactory(Player * p);

	/*******************************************************************************************************
	eventObserverFactory

	Recibe:
	GenericEvent * e: puntero donde el eventObserver va a buscar un evento

	Devuelve:
	eventObserver * : puntero al tileObserver de la tile recibida si no hay errores

	nullptr si ya se creo un tileObserver para la Tile recibida, si se recibe nullptr,
	o si no se puede construir el tileObserver

	//TODO: hacer bien
	********************************************************************************************************/
	eventObserver * eventObserverFactory(GenericEvent ** e);
	
	bool isValid();

	/*******************************************************************************************************
	tileObserverFactory

	Devuelve:
	ALLEGRO_DISPLAY * : puntero al display que se esta usando.

	NO ENTREGA OWNERSHIP DEL DISPLAY! SI LO DESTRUIS ESTALLA TODO
	********************************************************************************************************/
	ALLEGRO_DISPLAY * getDisplay();	//TODO: deberia estar????
	
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

	/*******************************************************************************************************
	getDisplaySection

	Recibe:
	unsigned int xPixel, yPixel: coordenadas en pixeles del punto donde se busca un displaySection

	Devuelve:
	contentBox * : -puntero al displaySection que se encuentra ahi si es que hay alguno
				   -nullptr si no hay un displaySection en ese punto

	Tiene undefined behaviour si hay contentBoxs superpuestos
	********************************************************************************************************/
	contentBox * getDisplaySection(unsigned int xPixel, unsigned int yPixel);
	
	ALLEGRO_EVENT_SOURCE * getDisplayEventSource();

	ALLEGRO_EVENT_SOURCE * getMenuEventSource();	//TODO: googlear la funcion de allegro que devuelve el menu event source

	/*******************************************************************************************************
	draw

	Dibuja todas las secciones del display.
	Si hubo un cambio de tamanio del display, se debe llamar primero a acknowledgeResize() para que
	se dibujen todos los elementos con las dimensiones correctas
	********************************************************************************************************/
	void draw();

private:

	/*******************************************************************************************************
	acknowledgeResize

	Actualiza las dimensiones de todos los elementos del display a las dimensiones actuales del display.
	********************************************************************************************************/
	void acknowledgeResize();

	contentBox * getDisplaySection(displaySection_t displaySection);

	void appendToTextlog(const char * msg);
	void appendToTextlog(std::string msg);

	void setTimeLeft(unsigned int timeLeft);

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