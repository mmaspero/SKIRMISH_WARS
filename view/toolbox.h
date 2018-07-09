#pragma once

#include <list>

#include "contentBox.h"
#include "../Game model/types.h"

typedef enum{EMPTY, SHOWING_ALL_PRODUCTS, SHOWING_ONE_PRODUCT, SHOWING_UNIT_INFO, N_TOOLBOX_STATUS}toolboxStatus_t;


class toolbox : public contentBox
{
public:
	toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height);
	~toolbox();

	void selectProduct(unit_t unitSpecificType);
	void deselectAllProducts();
	void setStatus(toolboxStatus_t status);
	toolboxStatus_t getStatus();
	virtual button * getButton(unsigned int xPixel, unsigned int yPixel);
	void goToStore();

private:
	toolboxStatus_t status;

	virtual void drawContent();
	virtual void resizeContent();
};

