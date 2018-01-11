#pragma once

#include "Player.h"
#include "Map.h"
#include <list>
#include "Move.h"
#include "Attack.h"

class Model {
public:
	Model(bool userStarts, char * map) { ; } //pasarle el path del mapa? o el mapa ya construido?
	~Model() { ; }
//	void run();


private:
	player_t turn;		//a que jugador le toca (neutral es de nadie, no se si pasaria en algun momento)
	Unit * active;		//unidad activa (es decir, ya la use y si decido usar otra no puedo usarla mas)
	Tile * selected;	//la primer tile seleccionada para una accion (capaz convendria tener solo un point, ver)
	std::list<Move> moves;
	std::list<Attack> attacks;

	Player user;
	Player opponent;
	Map m;
	//lista de observadores
};