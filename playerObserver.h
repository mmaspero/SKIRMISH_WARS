#pragma once
#include "observer.h"
#include "scoreBoard.h"
#include "Player.h"

class playerObserver :
	public observer
{
public:
	playerObserver(Player * p, scoreBoard * sB);
	~playerObserver();
	
	virtual void update();

private:
	Player * p;
	scoreBoard * sB;	//para poder mostrar la imagen
};

