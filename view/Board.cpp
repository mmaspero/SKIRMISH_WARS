#include "Board.h"
#include <iostream>
#include <algorithm>
#include <allegro5\allegro_primitives.h>

#define BOARD_LEFT_X contentStartX + (contentWidth  - tileSide * BOARD_WIDTH) / 2
#define BOARD_TOP_Y contentStartY + (contentHeight - tileSide * BOARD_HEIGHT) / 2

using namespace std;

Board::Board(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height)
	:contentBox(display, startX, startY, width, height, true)
{
	displaySectionType = BOARD;
	if (valid)
	{
		tileSide = min(contentWidth / BOARD_WIDTH, contentHeight / BOARD_HEIGHT);
	}
}

Board::~Board()
{
}

float Board::getTileSide()
{
	return tileSide;
}

tileButton * Board::getTileButton(unsigned int tileX, unsigned int tileY)
{
	if (tileX <= BOARD_WIDTH && tileY <= BOARD_HEIGHT)
	{
		return nullptr; //tileMap[tileX][tileY];
	}
	else
	{
		return nullptr;
	}
}

void Board::setTileButton(ALLEGRO_BITMAP * tileBmp, unsigned int tileX, unsigned int tileY)
{
	//crear un nuevo boton con la imagen recibida
	tileButton * tB = new tileButton(tileBmp, 
									BOARD_LEFT_X + tileX * tileSide, 
									BOARD_TOP_Y + tileY * tileSide, 
									tileSide, tileSide);
	if (tB->isValid()) 
	{
		buttonList.push_back(tB);	//TODO: avisar si es que no se cargo
	}
}

void Board::drawContent()
{
	al_draw_filled_rectangle(BOARD_LEFT_X, BOARD_TOP_Y, BOARD_LEFT_X + BOARD_WIDTH * tileSide, 
		BOARD_TOP_Y + BOARD_HEIGHT * tileSide, { 0,0,0,1 });	//TODO: placeholder del tablero

	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		(*it)->draw();
	}
}

void Board::resizeContent()
{
	tileSide = min(contentWidth / BOARD_WIDTH, contentHeight / BOARD_HEIGHT);
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		(*it)->resize(tileSide, tileSide);
	}
}
