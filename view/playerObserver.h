#pragma once
#include "observer.h"
#include "scoreBoard.h"
#include "toolbox.h"
#include "../Game model/Player.h"

class Player;

class playerObserver :
	public obs
{
public:
	playerObserver(Player * p, scoreBoard * sB, toolbox * t);
	~playerObserver();
	
	virtual void update();

private:
	Player * p;
	scoreBoard * sB;	//para poder mostrar la imagen
	toolbox * t;
};