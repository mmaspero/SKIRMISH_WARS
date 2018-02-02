#include "tileButton.h"



//TODO: Deberia borrar unformattedBmp o resizedBmp

tileButton::tileButton(float leftX, float topY, float width, float height, Point tilePosition)
	: button(leftX, topY, width, height)
{
	this->tilePosition = tilePosition;
}

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
	if (resizedBmp != nullptr)
	{
		al_draw_bitmap(resizedBmp, leftX, topY, 0);
	}
}

Point tileButton::getTilePosition()
{
	return tilePosition;
}
