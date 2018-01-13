#pragma once
#include "contentBox.h"
#include "tileButton.h"

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 12

enum{TERRENO, EJERCITO, CANT_DE_ELEMENTOS};
enum{TIERRA, AGUA, PLANTA, CANT_DE_TERRENOS};
enum{NADA, HOMBRE, MUJER, BEBE, CANT_DE_EJERCITOS};


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
	tileButton * tileMap[BOARD_WIDTH][BOARD_HEIGHT];	
	float tileSide;
};

