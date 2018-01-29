#pragma once

#include "Player.h"
#include "FSM\SkirmishFsm.h"
#include "Map.h"
#include <list>
#include "Move.h"
#include "Attack.h"
#include "../view/gui.h"

class Model {
public:
	Model(bool userStarts, char * map, player_t first, gui g); //pasarle el path del mapa? o el mapa ya construido? pasarle gui!
	~Model() { ; }

	bool validMove(Point p0, Point pf);		//estas es cuando llegan por paquete del otro jugador
	bool validAttack(Point p0, Point pf);
	bool validAction(action_t type, Point p0, Point pf);

	GenericEvent * tileSelected(Point p);	//puede devolver null si esa tile no es nada 

private:
	Unit * active;		//unidad activa (es decir, ya la use y si decido usar otra no puedo usarla mas)
	Tile * selected;	//la primer tile seleccionada para una accion (capaz convendria tener solo un point, ver)
	std::list<Action> moves;
	std::list<Attack> attacks;

	Player user;
	Player opponent;
	Map m;
	
	SkirmishFSM fsm;
	const gui& g;
};