#pragma once

#include "../Game model/Tile.h"
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
	void setTileButton(Tile * tile);
private:
	virtual void drawContent();
	virtual void resizeContent();
	float tileSide;
};

