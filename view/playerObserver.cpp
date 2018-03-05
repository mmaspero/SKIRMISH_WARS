#include "playerObserver.h"



playerObserver::playerObserver(Player * p, scoreBoard * sB, toolbox * t)
{
	this->p = p;
	this->sB = sB;
	this->t = t;
	
	if (p && sB && t)		//Si ninguno de los punteros es nullptr
	{
		valid = true;
	}
	else
	{
		valid = false;
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
		sB->setMyMoney(p->money);
		sB->setMyUnits(p->nUnits);
		sB->setMyCities(p->nCities);
		sB->draw();

		if (p->status == PURCHASING)
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
