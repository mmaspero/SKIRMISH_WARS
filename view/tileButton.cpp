#include "tileButton.h"



tileButton::tileButton(ALLEGRO_BITMAP * bmp, float leftX, float topY, float width, float height, Point tilePosition)
	: button(bmp, leftX, topY, width, height)
{
	this->tilePosition = tilePosition;
}

tileButton::~tileButton()
{
}

void tileButton::draw()
{
	al_draw_bitmap(resizedBmp, leftX, topY, 0);
}

Point tileButton::getTilePosition()
{
	return tilePosition;
}
