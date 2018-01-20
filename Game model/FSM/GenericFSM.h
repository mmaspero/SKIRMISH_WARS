#ifndef GENERIC_FSM
#define GENERIC_FSM

/*	

	Instituto Tecnológico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo práctico n° 5: FSM

	Autores:	González Bigliardi, Iñaki	- legajo 57.098
				Máspero, Martina			- legajo 57.120
				Parra, Rocío				- legajo 57.669

	Fecha de entrega: martes 11 de abril de 2017

*************************************************************************************************

	Máquina de estados finitos genérica.
	Para adaptarla a casos particulares, se debe redefinir la función dispatch() con los eventos
particulares que se deseen utilizar.

*/


#include "GenericState.h"

class GenericFSM
{
public:
	GenericFSM() {;}
	GenericFSM(GenericState * firstState) { currentState = firstState; }
	virtual void dispatch(GenericEvent& ev) = 0;
	virtual ~GenericFSM() { delete currentState ;}
	void setState(GenericState * state) {currentState = state;}
private:

protected:
	GenericState *currentState;

};


#endif //GENERIC_FSM
