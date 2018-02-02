#pragma once
#include "button.h"
#include "../Point.h"


class tileButton : public button
{
public:
	tileButton(float leftX, float topY, float width, float height, Point tilePosition);
	tileButton(ALLEGRO_BITMAP * bmp, float leftX, float topY, float width, float height, Point tilePosition);
	~tileButton();

	virtual void draw();
	Point getTilePosition();

private:
	Point tilePosition;
};

