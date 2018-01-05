#include "Board.h"
#include <iostream>
#include <algorithm>
#include <allegro5\allegro_primitives.h>

#define BOARD_LEFT_X contentStartX + (contentWidth  - tileSide * BOARD_WIDTH) / 2
#define BOARD_TOP_Y contentStartY + (contentHeight - tileSide * BOARD_HEIGHT) / 2

using namespace std;

Board::Board(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height, unsigned int (* map)[BOARD_WIDTH][BOARD_HEIGHT][CANT_DE_ELEMENTOS])
	:contentBox(display, startX, startY, width, height, true)
{
	if (valid)
	{
		srand(time(nullptr));

		tileSide = min(contentWidth / BOARD_WIDTH, contentHeight / BOARD_HEIGHT);

		imgTerrenos[TIERRA] = al_load_bitmap("media/img/dirtyTexture.png");
		imgTerrenos[AGUA] = al_load_bitmap("media/img/glassTexture.png");
		imgTerrenos[PLANTA] = al_load_bitmap("media/img/grassTexture2.png");

		imgEjercito[NADA] = nullptr;
		imgEjercito[HOMBRE] = al_load_bitmap("media/img/manSprite.png");
		imgEjercito[MUJER] = al_load_bitmap("media/img/womanSprite.png");
		imgEjercito[BEBE] = al_load_bitmap("media/img/babySprite.png");

		this->map = map;	//TODO: con referencia quizas?

	}		//TODO: agregar control de error por si no se cargan bien las imagenes
}

Board::~Board()
{
}

void Board::drawContent()
{
	ALLEGRO_BITMAP ** imgArray = nullptr;
	for (int k = 0; k < CANT_DE_ELEMENTOS; k++)
	{
		if (k == 0)
		{
			imgArray = imgTerrenos;
		}
		else if (k == 1)
		{
			imgArray = imgEjercito;
		}
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			for (int i = 0; i < BOARD_WIDTH; i++)
			{
				if (imgArray[(*map)[i][j][k]] != nullptr)
				{
					al_draw_scaled_bitmap(imgArray[(*map)[i][j][k]], 0, 0,
						al_get_bitmap_width(imgArray[(*map)[i][j][k]]), al_get_bitmap_height(imgArray[(*map)[i][j][k]]),
						BOARD_LEFT_X + i * tileSide, BOARD_TOP_Y + j * tileSide,
						tileSide, tileSide, 0);
				}
			}
		}
		al_flip_display();
	}
}

void Board::resizeContent()
{
	tileSide = min(contentWidth / BOARD_WIDTH, contentHeight / BOARD_HEIGHT);
}
