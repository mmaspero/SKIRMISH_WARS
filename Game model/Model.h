#pragma once

#include "Player.h"
#include "FSM\SkirmishFsm.h"
#include "Map.h"
#include <list>
#include "Action.h"
#include "../view/gui.h"
#include "../Controller/package/packages.h"

class Model {
public:
	Model(const char * map, player_t first, gui * g); //setea el model para los eventos skirmish!
	~Model();

	GenericEvent * validateOpponentAttack(attack att);		//estas es cuando llegan por paquete del otro jugador
	GenericEvent * validateOpponentMove(move mov);
	GenericEvent * validateOpponentPurchase(purchase purch);
	GenericEvent * getTileEvent(Point p);			//puede devolver null si esa tile no es nada 

private:
	Unit * active;		//unidad activa (es decir, ya la use y si decido usar otra no puedo usarla mas)
	Tile * selected;	//la primer tile seleccionada para una accion (capaz convendria tener solo un point, ver)
	std::list<Action *> actions;

	Player user;
	Player opponent;
	Map m;
	
	SkirmishFSM fsm;
	gui * g;
};