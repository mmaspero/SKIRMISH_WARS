#pragma once
#include "contentBox.h"
#include "tileButton.h"
#include "../Game model/types.h"

class Board : public contentBox
{
public:
	Board(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height);
	virtual ~Board();
	float getTileSide();
	tileButton * getTileButton(unsigned int tileX, unsigned int tileY);
	void setTileButton(ALLEGRO_BITMAP * tileBmp, unsigned int tileX, unsigned int tileY);
private:
	virtual void drawContent();
	virtual void resizeContent();
	float tileSide;
};

