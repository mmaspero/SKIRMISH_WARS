#pragma once
#include "sourceType.h"
#include "../../Game model/FSM/GenericEvent.h"
class eventSource
{
public:
	eventSource();
	~eventSource();
	/*setType
	recive como paramtero el tipo de fuente de evento
	que es, de a cuerdo con lo que indica sourceType.h*/
	void setType(sourceType type) { this->type = type; };
	
	/*getType
	devuelbe el tipo de fuente de evento, de a cuerdo con sourceType.h*/
	sourceType getType() { return type; };

	/*getEvent
	devuelve el evento ocurrido, y en caso de que ninguno ocurra
	devuelve NULL*/
	virtual GenericEvent * getEvent() = 0;
private:
	sourceType type;
};

