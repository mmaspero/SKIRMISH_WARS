#pragma once
#include "observer.h"
#include "scoreBoard.h"
#include "toolbox.h"
#include "gameStatus.h"
#include "../Game model/Player.h"

class Player;

class playerObserver :
	public obs
{
public:
	playerObserver(Player * p, scoreBoard * sB, toolbox * t, gameStatus * gs);	//no modifica p, sB, ni t
	~playerObserver();
	
	virtual void update();

private:
	Player * p;
	scoreBoard * sB;	//para poder mostrar la imagen
	gameStatus * gs;
	toolbox * t;
};