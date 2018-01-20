#ifndef GENERIC_FSM
#define GENERIC_FSM

/*	

	Instituto Tecnol�gico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo pr�ctico n� 5: FSM

	Autores:	Gonz�lez Bigliardi, I�aki	- legajo 57.098
				M�spero, Martina			- legajo 57.120
				Parra, Roc�o				- legajo 57.669

	Fecha de entrega: martes 11 de abril de 2017

*************************************************************************************************

	M�quina de estados finitos gen�rica.
	Para adaptarla a casos particulares, se debe redefinir la funci�n dispatch() con los eventos
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
