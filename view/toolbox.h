#pragma once

#include <list>

#include "contentBox.h"
#include "../Game model/types.h"
#include "../Game model/Unit.h"

typedef enum{EMPTY_MY_TURN, EMPTY_THEIR_TURN, SHOWING_ALL_PRODUCTS, SHOWING_ONE_PRODUCT, SHOWING_UNIT_INFO, N_TOOLBOX_STATUS}toolboxStatus_t;

class Unit;

class toolbox : public contentBox
{
public:
	toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height);
	~toolbox();

	void selectProduct(unit_t unitSpecificType);
	/* getSelectedProduct:
	si hay una unidad seleccionada, devuelve el unit_t correspondiente
	si no hay unidades seleccionadas, devuelve N_UNIT_TYPES
	*/
	unit_t getSelectedProduct();
	toolboxStatus_t getStatus();
	virtual button * getButton(unsigned int xPixel, unsigned int yPixel);
	void goToShowingUnitInfo(Unit * u);
	void goToStore();
	void goToMyTurn();
	void goToTheirTurn();
	void setProductCosts();

private:
	toolboxStatus_t status;
	Unit * u;	//Para sacar info en SHOWING_ONE_PRODUCT

	bool createSimpleButtons();
	
	virtual void drawContent();
	virtual void resizeContent();

	void drawEmptyMyTurn();
	void drawEmptyTheirTurn();
	void drawShowingAllProducts();
	void drawShowingOneProduct();
	void drawShowingUnitInfo();
};

