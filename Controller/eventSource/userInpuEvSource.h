#pragma once
#include "eventSource.h"
#include <allegro5/allegro.h>
#include"../../view/gui.h"
#include"../../Game model/Model.h"
class userInputEvSource: public eventSource
{
public:
	/*userInputEvSource
	recive como parametro un puntero a ALLEGRO_DISPLAY, ya inicializado*/
	userInputEvSource(ALLEGRO_DISPLAY * window, gui * usserInterface, Model * packageValidator);
	~userInputEvSource();
	
	/*InitOK
	devuelve true si la inicializacionde la fuente de eventos se realizo 
	correctamnete, y false en caso contrario*/
	bool InitOK() { return (!failToInit); };
	virtual GenericEvent * getEvent();

private:
	bool failToInit;
	ALLEGRO_DISPLAY * window;// diplay de allegro, debera estar ya inicializado
	ALLEGRO_EVENT_QUEUE * eventQueue;//cola de evntos donde se almacenan los eventos de allegro
	ALLEGRO_EVENT event;
	gui * usserInterface;
	Model * packageValidator;

};

