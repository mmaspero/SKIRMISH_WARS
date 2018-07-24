#pragma once
#include "network\network.h"
#include <iostream>
#include"package\packages.h"
#include "../view/gui.h"
#include "../Game model/Model.h"
#include "eventSource\eventGenerator.h"
#include "eventSource/timerEvSource.h"
#include "eventSource\eventSource.h"

class Controller
{
public:
	Controller(network * net, gui * usserInterface, Model * mod, eventGenerator * generadorDeEventos);
	~Controller();
	//todos los seners devuelve true si se pudo enviar correctamente el paquete.
	bool sendNameIs(std::string name);
	bool sendMapIs(std::string mapName, unsigned char checksum);
	bool sendMove(unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination);
	bool sendPurchase(std::string ejercitoID, unsigned char row, unsigned char column);
	bool sendAttack(unsigned char dice, unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination);
	/*sendOneBytePackage, recive como argumento el tipo de paquete que se desea 
	enviar. 
	el tipo de paquete se encuentra en packages.h donde dise tipo de paquetes de
	datos.*/
	bool sendOneBytePackage(unsigned char type);

	//funciones de play timer
	void startPlayTimer();
	void resetPlayTimer();
	void stopPlayTimer();
	void run();
	gui * getGui() { return usserInterface;};
	eventSource * getTurnTimer() { return &gameTimer; };
private:
	network * net;
	bool sendPackage(genericPackage * package);
	gui * usserInterface;
	Model * mod;
	eventGenerator * generadorDeEventos;
	timerEvSource gameTimer;
	

};

