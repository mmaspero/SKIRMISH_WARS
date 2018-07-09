#include "playerObserver.h"

#include <iostream>

playerObserver::playerObserver(Player * p, scoreBoard * sB, toolbox * t, gameStatus * gs)
{
	this->p = p;
	this->sB = sB;
	this->t = t;
	this->gs = gs;
	
	if (p && sB && t && gs)		//Si ninguno de los punteros es nullptr
	{
		valid = true;
	}
	else
	{
		valid = false;
		std::cout << "No se pudo crear el player observer" << std::endl;
	}
}

playerObserver::~playerObserver()
{
}

void playerObserver::update()
{
	if (p->who == OPPONENT) 
	{
		//actualizo su HQ HP
		sB->getTheirHQHPbar()->setCurrentHP(p->capturePointsHQ);	//TODO: capture points es lo mismo que hp??
		sB->draw();
	}
	else if (p->who == USER)
	{
		sB->getMyHQHPbar()->setCurrentHP(p->capturePointsHQ);
		gs->setMoney(p->money);
		gs->setUnitCount(p->nUnits);
		gs->setCityCount(p->nCities);
		sB->draw();
		gs->draw();

		if (p->status == WAITING)
		{
			

			//TODO: !!!!!!!!!!!!!!!!!!!!!!! EN EL HEADER DE RO DECIA UNIT, NO UNIT *
//			std::list<Unit *> possiblePurchases = p->getPossiblePurchases();
			
			
			//draw(possiblePurchases);
		}
	}
	else
	{
		//TODO: explota todo o ke?
	}



	//SI ES EL DE LA COMPU:
	//actualizo la plata, la HP del HQ, cant de unidades
	//
	//estoy comprando o moviendo/atacando?
	//SI ESTOY MOVIENDO NO HAGO NADA MAS
	//SI ESTOY COMPRANDO, en Player busco 1)todas las unidades 2)para cuales me alcanza la plata

}
