#pragma once
#include "contentBox.h"
class optionBox :
	public contentBox
{
public:
	optionBox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height);
	~optionBox();
	virtual void drawContent() {};
	virtual void resizeContent() {};
};

