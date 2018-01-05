#include "playerStats.h"

#include <algorithm>
#include <iostream>

#include "config/playerStats_config.h"

using namespace std;

playerStats::playerStats(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height) 
	: contentBox(display, startX, startY, width, height)
{
	if (valid)	//construir playerStats solo si no hubieron problemas en el constructor de contentBox
	{
		ALLEGRO_BITMAP * timeSprite = al_load_bitmap(TIME_SPRITE_FILE);		//TODO: esto deberia estar aca? 
		myStats[MONEY].bitmap = al_load_bitmap(COIN_SPRITE_FILE);			//TODO: alguna manera de cargarlas de una a todo el arreglo con un for?
		myStats[ARMIES].bitmap = al_load_bitmap(ARMY_SPRITE_FILE);

		if (timeSprite == nullptr)
		{
			cout << "problema cargando el sprite del reloj" << endl;
			valid = false;
		}
		for(int i = 0; (i < AMOUNT_OF_STATS)&&(valid == true); i++)
		{
			if (myStats[i].bitmap == nullptr)
			{
				cout << "problema cargando las imagenes de las stats" << endl;
				valid = false;
			}
		}

		myStats[MONEY].statValue = string("2456");
		myStats[ARMIES].statValue = string("367,5");	//TODO: borrar, es de debug

		if (!(font = al_load_font(FONT_NAME, FONT_SIZE, 0)))	//TODO: magic numbers
		{
			cout << "problema cargando font de stats" << endl;
			valid = false;
		}

		lineHeight = al_get_font_line_height(font);
	}
}

playerStats::~playerStats()
{
	al_destroy_font(font);
}

void playerStats::drawStat(statLine stat, unsigned int x, unsigned int y)
{	
	//TODO: dejar al_draw_scaled_bitmap o hacer un nuevo bitmap del tamanio indicado?

	unsigned int bmpWidth = al_get_bitmap_width(stat.bitmap);
	unsigned int bmpHeight = al_get_bitmap_height(stat.bitmap);

	double longestEdge = (double)max(bmpWidth, bmpHeight);
	double resizingFactor = ((double)lineHeight) / longestEdge;

	al_draw_scaled_bitmap(stat.bitmap, 0, 0,
						  bmpWidth, bmpHeight,
						  x, y, resizingFactor * bmpWidth, resizingFactor * bmpHeight, 0);

	al_draw_text(font, al_map_rgba_f(0, 0, 0, 0.6), x + lineHeight + 2, y + 2, 0, stat.statValue.c_str());	//TODO: sacar magic numbers
	al_draw_text(font, al_map_rgb_f(1, 1, 1), x + lineHeight, y, 0, stat.statValue.c_str());
}

void playerStats::drawContent()
{
	for (int i = 0; i < AMOUNT_OF_STATS; i++)
	{
		drawStat(myStats[i], contentStartX, contentStartY + lineHeight * i);
	}
}

void playerStats::resizeContent()
{

}
