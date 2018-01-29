#include "optionBox.h"



optionBox::optionBox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height)
	:contentBox(display, startX, startY, width, height, true)
{
}


optionBox::~optionBox()
{
}
