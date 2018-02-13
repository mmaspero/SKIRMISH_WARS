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
	Model(const char * map, player_t first, std::list<GenericEvent *> * softwareEvents, gui * g);
	// deja al model listo para empezar a jugar!
	// parametros que recibe:
	// - map:	string con el path del archivo de coma separated values donde esta la info del mapa
	//			que se va a usar en la partida
	// - first: que jugador empieza. si no es ni USER, asume que es OPPONENT
	// - softwareEvents:	puntero a la lista donde va a registrar eventos de software. ESA LISTA
	//						DEBE TENER PRIORIDAD SOBRE LA DE EVENTOS DE RED
	//	- g: puntero a la gui ya construida. si esta definido DEBUG_NOVIEW, no lo utiliza

	//	EL MODEL DEBE DESTRUIRSE UNA VEZ TERMINADA LA PARTIDA, si hay que hacer un rematch
	//aunque sea con el mismo mapa hay que destruirlo y 

	~Model();
	bool isValid();

	// validacion de paquetes de red: devuelven nullptr si el paquete recibido no es valido en el el estado
	//del juego actual, pero NO registra automaticamente un error en el juego 
	GenericEvent * validateOpponentAttack(attack * att);		
	GenericEvent * validateOpponentMove(move * mov);
	GenericEvent * validateOpponentPurchase(purchase * purch);

	// getTileEvent: recibe la fila y la columna de la tile que el jugador selecciono.
	// si la seleccion no resulta en ningun evento valido, devuelve nullptr
	GenericEvent * getTileEvent(Point p);			
	
	// dispatch: devuelve false si se registro algun comportamiento no valido en el juego,
	// y detiene el juego en ese caso. si le envio nullptr o un evento que no tiene en consi-
	// deracion no pasa nada
	bool dispatch(GenericEvent * ev);

	// playerWon: devuelve true si el jugador indicado gano. si no es USER asume que es OPPONENT
	bool playerWon(player_t p);

	void notifyUserVictory();

	// muestra las fabricas libres del jugador cuyo turno es actualmente.
	// para dejar de mostrarlas, llamar a clearActions
	void showAvailableFactories();

	// muestra los posibles movimientos y ataques de la unidad que se encuentra en p.
	// lo primero que hace es llamar a clearActions!
	void showPossibleActions(Point p);

	// vuelve a su estado previo a las tiles que se habia cambiado con las funciones
	// showPossibleActions o showAvailableFactories
	void clearActions();

	// realiza un update de todas las tiles, teniendo en cuenta el turno de quien es ahora.
	// si detecta que los HQ de un jugador fueron capturados, registra que ese jugador perdio
	// suma al usuario cuyo turno comienza el dinero que le corresponde 
	bool nextTurn();

	bool registerAttack(Point origin, Point target, unsigned int dice); 
	void endAttack(Point attacker); 
	bool registerMove(Point p0, Point pf);
	bool registerPurchase(player_t who, Point factory, unit_t type);

private:
	bool valid;

	player_t turn;
	Unit * activeUnit;	//para saber cuando pasarla a post-active
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