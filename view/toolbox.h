#pragma once

#include <list>

#include "contentBox.h"
#include "../Game model/types.h"



class toolbox : public contentBox
{
public:
	toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height);
	~toolbox();

	void selectProduct(unit_t unitSpecificType);
	void deselectAllProducts();

private:
	virtual void drawContent();
	virtual void resizeContent();

//	productButton * unitsToBuy[N_TYPES];
};

