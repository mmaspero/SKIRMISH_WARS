#include "toolbox.h"

#include "simpleButton.h"
#include "productButton.h"

#define BUTTONS_PER_ROW 3



toolbox::toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height)
	: contentBox(display, startX, startY, width, height, false)	//TODO: sacar magic numbers
{
	if (valid)
	{
		displaySectionType = TOOLBOX;

		status = EMPTY_MY_TURN;

		bool buttonValid = true;
		float productButtonSectionHeight = 0.9 * contentHeight;	//TODO: sacar magic number
		productButton * b = nullptr;

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
		resizeContent();

		simpleButton * simpleBuy = new simpleButton(BUY_BUTTON, contentStartX, contentStartY + contentHeight * 0.9,
			contentWidth / 2, contentHeight * 0.1);
		buttonList.push_back(simpleBuy);
		if(!buttonList.back()->isValid())
		{
			buttonValid = false;
		}

		simpleButton * simpleStore = new simpleButton(STORE_BUTTON, contentStartX, contentStartY + contentHeight * 0.9,
			contentWidth / 2, contentHeight * 0.1);
		buttonList.push_back(simpleStore);
		if (!buttonList.back()->isValid())
		{
			buttonValid = false;
		}

		simpleButton * simpleBack = new simpleButton(BACK_BUTTON, contentStartX + contentWidth / 2.0, contentStartY + contentHeight * 0.9,
					contentWidth / 2, contentHeight * 0.1);
		buttonList.push_back(simpleBack);
		if (!buttonList.back()->isValid())
		{
			buttonValid = false;
		}

		simpleButton * simplePass = new simpleButton(PASS_BUTTON, contentStartX + contentWidth / 2.0, contentStartY + contentHeight * 0.9,
			contentWidth / 2, contentHeight * 0.1);
		buttonList.push_back(simplePass);
		if (!buttonList.back()->isValid())
		{
			buttonValid = false;
		}


		if (!buttonValid)	//Si hubo un error en el constructor de algun boton, eliminar toda la lista
		{
			buttonList.clear();
		}
		valid = buttonValid;
	}
}

toolbox::~toolbox()
{
	//TODO:
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
			case EMPTY_MY_TURN:
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
			case SHOWING_UNIT_INFO:
				break;
			}

		}
	}
	return buttonSelected;
}

void toolbox::goToStore()
{
	if (status == EMPTY_MY_TURN || status == SHOWING_ONE_PRODUCT)
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
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->hiddenOff();
			((productButton *)(*it))->selectedOff();
		}
	}
}

void toolbox::drawContent()
{
	switch (status)	//EMPTY_THEIR_TURN no tiene nada que dibujar
	{
	case EMPTY_MY_TURN:
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->isValid())
			{
				button * b = (*it);
				if (b->getType() == SIMPLE_BUTTON && 
					(((simpleButton*)b)->isItStore() || ((simpleButton*)b)->isItPass()) )
				{
					b->draw();
				}
			}
		}
		break;
	case SHOWING_ALL_PRODUCTS:
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->isValid())
			{
				button * b = (*it);
				if (b->getType() == PRODUCT_BUTTON)
				{
					b->draw();
				}
				else if (b->getType() == SIMPLE_BUTTON && ((simpleButton*)b)->isItPass() )
				{
					b->draw();
				}
			}	
		}
		break;
	case SHOWING_ONE_PRODUCT:
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->isValid())
			{
				button * b = (*it);
				if (b->getType() == PRODUCT_BUTTON)
				{
					if (b->isSelected())
					{
						b->draw();
					}
				}
				else if (b->getType() == SIMPLE_BUTTON &&
					(((simpleButton*)b)->isItBack() || ((simpleButton*)b)->isItBuy()))
				{
					b->draw();
				}
			}	//TODO: hacer mas compacto pero no croto
		}
		break;
	case SHOWING_UNIT_INFO:
		//TODO:
		break;
	}
}

void toolbox::resizeContent()
{

	float productButtonSectionHeight = 0.9 * contentHeight;	//TODO: sacar magic number

	for (std::list<button*>::iterator it = buttonList.begin(); 
		it != buttonList.end(); 
		it++)
	{
		unit_t unitSpecificType = ((productButton*)(*it))->getUnitSpecificType();


		int aux = (unitSpecificType % BUTTONS_PER_ROW);

		float rWidth = contentWidth / (float)BUTTONS_PER_ROW;
		float rHeight = productButtonSectionHeight / (N_UNIT_TYPES / (int)BUTTONS_PER_ROW);
		float rLeftX = contentStartX + rWidth * aux;
		float rTopY = contentStartY + rHeight * (unitSpecificType / (int)BUTTONS_PER_ROW);


		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->setAllDimensions(//Unit * u
				rLeftX, rTopY, rWidth, rHeight,
				contentStartX, contentStartY, contentWidth, contentHeight);
		}

	}
}
