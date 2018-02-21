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

		status = EMPTY;

		bool buttonValid = true;
		float productButtonSectionHeight = 0.9 * contentHeight;	//TODO: sacar magic number
		for (int i = 0; i < N_UNIT_TYPES; i++)
		{
			int aux = (i % BUTTONS_PER_ROW);

			float rWidth = contentWidth / (float)BUTTONS_PER_ROW;
			float rHeight = productButtonSectionHeight / (N_UNIT_TYPES / (int)BUTTONS_PER_ROW);
			float rLeftX = contentStartX + rWidth * aux;
			float rTopY = contentStartY + rHeight * (i / (int)BUTTONS_PER_ROW);

			buttonList.push_back(new productButton(//Unit * u
				rLeftX, rTopY, rWidth, rHeight,
				contentStartX, contentStartY, contentWidth, contentHeight, (unit_t)i));
			if (!buttonList.back()->isValid())
			{
				buttonValid = false;
			}
		}

		simpleButton * simpleBuy = new simpleButton(BUY, contentStartX, contentStartY + contentHeight * 0.9,
			contentWidth / 2, contentHeight * 0.1);
		buttonList.push_back(simpleBuy);
		if(!buttonList.back()->isValid())
		{
			buttonValid = false;
		}

		simpleButton * simpleBack = new simpleButton(BACK, contentStartX + contentWidth / 2.0, contentStartY + contentHeight * 0.9,
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
}

void toolbox::selectProduct(unit_t unitSpecificType)
{
	for (std::list<button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
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
	status = SHOWING_ONE_PRODUCT;
}

void toolbox::deselectAllProducts()
{
	for (std::list<button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		((productButton *)(*it))->selectedOff();
		((productButton *)(*it))->hiddenOff();
	}
	status = SHOWING_ALL_PRODUCTS;
}

void toolbox::drawContent()
{
	switch (status)
	{
	case EMPTY:
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->isValid())
			{
				button * b = (*it);
				if (b->getType() == SIMPLE_BUTTON && 
					(((simpleButton*)b)->isItBuy() || ((simpleButton*)b)->isItPass()) )
				{
					b->draw();
				}
			}	//TODO: hacer mas compacto pero no croto
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
			}	//TODO: hacer mas compacto pero no croto
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
	int i = 0; //TODO: sacar!!! hacer solo con unitSpecificType
	for (std::list<button*>::iterator it = buttonList.begin(); 
		it != buttonList.end(); 
		it++)
	{
		unit_t unitSpecificType = ((productButton*)(*it))->getUnitSpecificType();

		float rWidth = contentWidth / (float)BUTTONS_PER_ROW;
		float rHeight = contentHeight / (N_UNIT_TYPES / (int)BUTTONS_PER_ROW);
		float rLeftX = contentStartX + rWidth * (i % BUTTONS_PER_ROW);//(unitSpecificType % BUTTONS_PER_ROW);
		float rTopY = contentStartY + rHeight * (i / (int)BUTTONS_PER_ROW);//((int)unitSpecificType / (int)BUTTONS_PER_ROW);


		((productButton *)(*it))->setAllDimensions(//Unit * u
			rLeftX, rTopY, rWidth, rHeight,
			contentStartX, contentStartY, contentWidth, contentHeight);
		i++;
	}
}
