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
		//TODO: agregar los simpleButtons;
		simpleButton * simpleBuy = new simpleButton(BUY, contentStartX + contentWidth / 2, contentStartY + height * 0.9,
			contentWidth / 2, contentHeight * 0.9);
		if (simpleBuy->isValid())
		{
			buttonList.push_back(simpleBuy);
		}
		simpleButton * simpleBack = new simpleButton(BACK, contentStartX, contentStartY + height * 0.9,
					contentWidth / 2, contentHeight * 0.9);
		if(simpleBack->isValid())
		{
			buttonList.push_back(simpleBack);
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
}

void toolbox::deselectAllProducts()
{
	for (std::list<button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		((productButton *)(*it))->selectedOff();
		((productButton *)(*it))->hiddenOff();
	}

}

void toolbox::drawContent()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		(*it)->draw();
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
