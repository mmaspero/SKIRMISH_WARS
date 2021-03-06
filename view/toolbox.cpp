#include "toolbox.h"

#include <iostream>

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include "simpleButton.h"
#include "productButton.h"
#include "config\toolbox_config.h"
#include "HPbar.h"
#include "paths.h"	




using namespace std;

toolbox::toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height)
	: contentBox(display, startX, startY, width, height, false)
{
	if (valid)
	{
		displaySectionType = TOOLBOX;

		status = EMPTY_MY_TURN;	//TODO: que no empiece siempre en  mi turno.

		bool buttonValid = true;
		productButton * b = nullptr;

		//creo los product button con tamanios arbitrarios.
		for (int i = 0; i < N_UNIT_TYPES; i++)
		{
			b = new productButton(//Unit * u
				1,1,1,1,1,1,1,1, (unit_t)i);
			b->hiddenOn();
			b->selectedOff();
			buttonList.push_back(b);
			if (!buttonList.back()->isValid())
			{
				buttonValid = false;
			}
		}
		//Seteo el tamanio de los productButtons y creo los simpleButtons
		resizeContent();

		//Si hubo un error en el constructor de algun boton, eliminar toda la lista
		if (!buttonValid)	
		{
			buttonList.clear();
		}
		valid = buttonValid;
	}
}

toolbox::~toolbox()
{
	buttonList.clear();
}

void toolbox::selectProduct(unit_t unitSpecificType)
{
	for (std::list<button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			if (((productButton *)(*it))->getUnitSpecificType() == unitSpecificType)
			{
				((productButton *)(*it))->selectedOn();
				((productButton *)(*it))->hiddenOff();
			}
			else
			{
				((productButton *)(*it))->selectedOff();
				((productButton *)(*it))->hiddenOn();
			}
		}
	}
	status = SHOWING_ONE_PRODUCT;
}

unit_t toolbox::getSelectedProduct()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON && ((productButton *)(*it))->isSelected())
		{
			return ((productButton *)(*it))->getUnitSpecificType();
		}
	}
	return N_UNIT_TYPES;
}

bool toolbox::isItShowingThisUnitInfo(Unit * u)
{
	return this->u == u;
}

toolboxStatus_t toolbox::getStatus()
{
	return status;
}

button * toolbox::getButton(unsigned int xPixel, unsigned int yPixel)
{
	button * buttonSelected = nullptr;
	

	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isItHere(xPixel, yPixel))
		{
			switch (status)
			{
			case EMPTY_MY_TURN: case SHOWING_UNIT_INFO:
				if ((*it)->getType() == SIMPLE_BUTTON && 
					(((simpleButton *)(*it))->getSimpleType() == STORE_BUTTON || ((simpleButton *)(*it))->getSimpleType() == PASS_BUTTON))
				{
					buttonSelected = (*it);
				}
				break;
			case SHOWING_ONE_PRODUCT:
				if ((*it)->getType() == SIMPLE_BUTTON &&
					(((simpleButton *)(*it))->getSimpleType() == BACK_BUTTON || ((simpleButton *)(*it))->getSimpleType() == BUY_BUTTON))
				{
					buttonSelected = (*it);
				}
				break;
			case SHOWING_ALL_PRODUCTS:
				if ( (*it)->getType() == PRODUCT_BUTTON ||
					((*it)->getType() == SIMPLE_BUTTON && ((simpleButton *)(*it))->getSimpleType() == PASS_BUTTON ))
				{
					buttonSelected = (*it);
				}
				break;
			default:
				break;
			}

		}
	}
	return buttonSelected;
}

void toolbox::goToShowingUnitInfo(Unit * u)
{
	status = SHOWING_UNIT_INFO;

	this->u = u;
}

void toolbox::goToStore()
{
	u = nullptr;
	if (status == EMPTY_MY_TURN || status == SHOWING_ONE_PRODUCT || status == SHOWING_UNIT_INFO)
	{
		status = SHOWING_ALL_PRODUCTS;
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->getType() == PRODUCT_BUTTON)
			{
				((productButton *)(*it))->hiddenOff();
				((productButton *)(*it))->selectedOff();
			}
		}
	}
}

void toolbox::goToMyTurn()
{

	status = EMPTY_MY_TURN;
	u = nullptr;
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->hiddenOn();
			((productButton *)(*it))->selectedOff();
		}
	}
}

void toolbox::goToTheirTurn()
{
	status = EMPTY_THEIR_TURN;
	u = nullptr;
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->hiddenOff();
			((productButton *)(*it))->selectedOff();
		}
	}
}

void toolbox::setProductCosts()
{
	acknowledgeResize();	//Para que se creen los bmps con el precio.
}

void toolbox::setMyMoney(unsigned int myMoney)
{
	this->myMoney = myMoney;
	setCanBuy();
}

void toolbox::setCanBuy()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid() && (*it)->getType() == PRODUCT_BUTTON)
		{
			productButton * b = ((productButton *)(*it));
			b->setCanBuy(Unit::getCost(b->getUnitSpecificType()) <= myMoney);
		}
	}
}


bool toolbox::createSimpleButtons()
{
	bool buttonValid = true;		//indica si hubo un error en la creacion de alguno de los botones.

	//dimensiones y coordenadas de los botones. 
	//Lo unico que cambia en los diferentes simpleButtons la coordenada x
	//(la coordenada y, el ancho, y el alto se mantienen)

	float buttonHeight = contentHeight * (1 - PRODUCT_SECTION_RELATIVE_H);
	float buttonWidth = contentWidth / 2.0;
	float buttonTopY = contentStartY + contentHeight * PRODUCT_SECTION_RELATIVE_H;

	simpleButton * simpleBuy = new simpleButton(BUY_BUTTON, 
		contentStartX,
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleBuy);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simpleStore = new simpleButton(STORE_BUTTON, 
		contentStartX, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleStore);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simpleBack = new simpleButton(BACK_BUTTON, 
		contentStartX + contentWidth / 2.0, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleBack);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simplePass = new simpleButton(PASS_BUTTON, 
		contentStartX + contentWidth / 2.0, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simplePass);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	return buttonValid;
}

void toolbox::drawContent()
{
	switch (status)
	{
	case EMPTY_MY_TURN:
		drawEmptyMyTurn();
		break;
	case SHOWING_ALL_PRODUCTS:
		drawShowingAllProducts();
		break;
	case SHOWING_ONE_PRODUCT:
		drawShowingOneProduct();
		break;
	case SHOWING_UNIT_INFO:
		drawShowingUnitInfo();
		break;
	}
}

void toolbox::resizeContent()
{
	float productButtonSectionHeight = PRODUCT_SECTION_RELATIVE_H * contentHeight;
	std::list<button*>::iterator it = buttonList.begin();

	do
	{

		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			unit_t unitSpecificType = ((productButton*)(*it))->getUnitSpecificType();

			int aux = (unitSpecificType % BUTTONS_PER_ROW);

			float rWidth  = contentWidth / (float)BUTTONS_PER_ROW;
			float rHeight = productButtonSectionHeight / (N_UNIT_TYPES / (int)BUTTONS_PER_ROW);
			float rLeftX  = contentStartX + rWidth * aux;
			float rTopY   = contentStartY + rHeight * (unitSpecificType / (int)BUTTONS_PER_ROW);

			((productButton *)(*it))->setAllDimensions(
				rLeftX, rTopY, rWidth, rHeight,
				contentStartX, contentStartY, contentWidth, PRODUCT_SECTION_RELATIVE_H * contentHeight);
			it++;	
		}
		else if ((*it)->getType() == SIMPLE_BUTTON)
		{
			it = buttonList.erase(it);		//el iterador se incrementa en erase()
		}
	} while (it != buttonList.end());
	//como buttonList.erase(it) incrementa el iterador, no lo incremento en el statement de salida del while 

	createSimpleButtons();
}

void toolbox::drawEmptyMyTurn()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid())
		{
			button * b = (*it);
			if (b->getType() == SIMPLE_BUTTON &&
				(((simpleButton*)b)->isItStore() || ((simpleButton*)b)->isItPass()))
			{
				b->draw();
			}
		}
	}
}

void toolbox::drawEmptyTheirTurn()
{
}

void toolbox::drawShowingAllProducts()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid())
		{
			button * b = (*it);
			if (b->getType() == PRODUCT_BUTTON)
			{
				b->draw();
			}
			else if (b->getType() == SIMPLE_BUTTON && ((simpleButton*)b)->isItPass())
			{
				b->draw();
			}
		}
	}
}

void toolbox::drawShowingOneProduct()
{
	productButton * selectedProduct = nullptr;
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid() && (*it)->getType() == PRODUCT_BUTTON)
		{
			if ((*it)->isSelected())
			{
				(*it)->draw();
				selectedProduct = ((productButton *)(*it));
			}
		}	
	}
	if (selectedProduct == nullptr)
	{
		return;
	}
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid() && (*it)->getType() == SIMPLE_BUTTON)
		{
			simpleButtonType_t simpleType = ((simpleButton *)(*it))->getSimpleType();
			if (simpleType == BACK_BUTTON || (simpleType == BUY_BUTTON && selectedProduct->getCanBuy()))
			{
				(*it)->draw();
			}
		}

	}
}

void toolbox::drawShowingUnitInfo()
{
	if (u == nullptr || u->getType() == N_UNIT_TYPES) { return; }

	//Creo boton auxiliar para usar el expandedBmp para mostrar la unit info.
	productButton auxButton(10, 10, 10, 10, 10, 10,	
		contentWidth, contentHeight * PRODUCT_SECTION_RELATIVE_H, u->getType());

	if (!auxButton.isValid()) { return; }
	
	ALLEGRO_BITMAP * unitInfoBmp = auxButton.getShowingUnitInfoBmp(u);
	drawEmptyMyTurn();
	al_draw_bitmap(unitInfoBmp, contentStartX, contentStartY, 0);
	al_destroy_bitmap(unitInfoBmp);

	}