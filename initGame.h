#pragma once
#include "Controller\network\network.h"
#include <vector>
#include "view\pipBoy.h"
#include <allegro5/allegro.h>
#include <iostream>
#include "Controller\eventSource\timerEvSource.h"
class initGame
{
public:
	initGame();
	~initGame();
	bool startGame();
	bool initOK() { return okInit; };
	network * getNet() { return net; };
	std::string getName() { return name; };


private:
	bool ipOK();
	bool allegroInicializacion();
	bool allegroDestruccion();
	bool okInit;
	network * net;
	std::vector<std::string> mapPaths;
	pipBoy * guiInitGame;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * CEventos;
	ALLEGRO_EVENT ev;
	std::string ip_;
	std::string name;
	timerEvSource timeOutNet;

};
