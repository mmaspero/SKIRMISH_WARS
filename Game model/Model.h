#pragma once

#include "Player.h"
#include "FSM\SkirmishFsm.h"
#include "Map.h"
#include <list>
#include "Action.h"
#include "../view/gui.h"
#include "../Controller/package/packages.h"

//#define DEBUG_NOVIEW	1

class Model {
public:
	Model(const char * map, player_t first, std::list<GenericEvent *> * softwareEvents, gui * g); //setea el model para los eventos skirmish!!	
	~Model();
	bool isValid();

	GenericEvent * validateOpponentAttack(attack * att);		//estas es cuando llegan por paquete del otro jugador
	GenericEvent * validateOpponentMove(move * mov);
	GenericEvent * validateOpponentPurchase(purchase * purch);
	GenericEvent * getTileEvent(Point p);			//puede devolver null si esa tile no es nada 
	bool dispatch(GenericEvent * ev);

	void showPossibleActions(Point p);
	void clearActions();
	bool nextTurn();
	bool registerAttack(Point origin, Point target, unsigned int dice); 
	//FALTA SACAR LA FOG CUANDO TE ATACAN DE UNA TILE QUE NO VES!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//bool registerCounterAttack(Point origin, Point target, unsigned int dice);
	void endAttack(Point attacker); 
	bool registerMove(Point p0, Point pf);
	bool registerPurchase(player_t who, Point factory, unit_t type);

private:
	bool valid;

	player_t turn;
	Unit * activeUnit;	//para saber cuando pasarla a post-active
	//Point target;		//para saber de donde tengo que esperar un contraataque
	//Point selected;	//la primer tile seleccionada para una accion
	std::list<Action> actions;

	Player user;
	Player opponent;
	Map m;
	
	SkirmishFSM fsm;

	Player * currPlayer();
	void updateActiveUnit(Unit * u);
	void checkForUnitDeath(Point where);
	std::list<GenericEvent *> * softwareEvents;
};