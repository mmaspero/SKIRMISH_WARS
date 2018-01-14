#pragma once

typedef enum 
{
	MOUSE_HOVER_BUTTON, 
	MOUSE_PRESS_BUTTON, 
	MOUSE_RELEASE_BUTTON,
	DISPLAY_CLOSE,
	DISPLAY_RESIZE,
	INVALID_MOVEMENT,	//Textlog: no se puede realizar el movimiento, tirar info sobre movimientos validos y cuando se puede mover y cuando no
	INVALID_ATTACK,	//Textlog: lo mismo que INVALID_MOVEMENT
	OPPONENT_QUIT,
	OPPONENT_PASS,
	USER_WON,
	USER_LOST,
	NETWORK_ERROR,	//Cualquier error de red.
	SECOND_ELAPSED,
	TIMEOUT,	//Timeout de mi turno.
	EVENT_N
} eventType_t;

class genericEvent
{
public:
	genericEvent();
	~genericEvent();

	eventType_t getEventType();

private:
	eventType_t eventType;
};

