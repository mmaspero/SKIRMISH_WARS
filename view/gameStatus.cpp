#include "gameStatus.h"
#include <iostream>
#include <string>
#include <cmath>
#include "paths.h"

#define TIME_BMP IMAGE_PATH "clock.png"
#define UNIT_BMP IMAGE_PATH "manSprite.png"
#define COIN_BMP IMAGE_PATH "coin.png"

#define DEFAULT_FONT FONT_PATH "PressStart2P.ttf"
#define FONT_COLOR "black"
#define FONT_HEIGHT_IN_BITMAP_HEIGHT (3.0/4.0)

using namespace std;

unsigned int getDigitCount(unsigned int n);

gameStatus::gameStatus(ALLEGRO_DISPLAY * display, float startX, float startY, 
	float width, float height, bool isBoxTransparent)
	: contentBox(display, startX, startY, width, height, true)
{
	if (valid)
	{
		displaySectionType = GAMESTATUS;
		timeStat.value = unitStat.value = moneyStat.value = 0;
		
		ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();

		//crear un bitmap con el tamanio adecuado (cuadrado de maxima altura posible)
		//y dibujar la imagen del reloj con esas dimensiones
		ALLEGRO_BITMAP * auxBmp = al_load_bitmap(TIME_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se pudo cargar la imagen del reloj " << TIME_BMP << endl; 
			valid = false;
			return;
		}
		timeStat.bmp = al_create_bitmap(contentHeight, contentHeight);
		al_set_target_bitmap(timeStat.bmp);
		al_draw_scaled_bitmap(auxBmp, 0, 0, al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
			0, 0, al_get_bitmap_width(timeStat.bmp), al_get_bitmap_height(timeStat.bmp), 0);
		
		//lo mismo para las imagenes de plata y de unidades
		auxBmp = al_load_bitmap(UNIT_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se pudo cargar la imagen de una unidad " << UNIT_BMP << endl;
			valid = false;
			return;
		}
		unitStat.bmp = al_create_bitmap(contentHeight, contentHeight);
		al_set_target_bitmap(unitStat.bmp);
		al_draw_scaled_bitmap(auxBmp, 0, 0, al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
			0, 0, al_get_bitmap_width(unitStat.bmp), al_get_bitmap_height(unitStat.bmp), 0);

		auxBmp = al_load_bitmap(COIN_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se pudo cargar la imagen de la moneda " << COIN_BMP << endl;
			valid = false;
			return;
		}
		moneyStat.bmp = al_create_bitmap(contentHeight, contentHeight);
		al_set_target_bitmap(moneyStat.bmp);
		al_draw_scaled_bitmap(auxBmp, 0, 0, al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
			0, 0, al_get_bitmap_width(moneyStat.bmp), al_get_bitmap_height(moneyStat.bmp), 0);
		
		al_set_target_bitmap(backupBmp);

		font = al_load_font(DEFAULT_FONT, -contentHeight * FONT_HEIGHT_IN_BITMAP_HEIGHT, 0);
		if (font == nullptr)
		{
			cout << "No se pudo cargar la font de gameStats " << DEFAULT_FONT << endl;
			valid = false;
			return;
		}
	}
}

gameStatus::~gameStatus()
{
	if (timeStat.bmp != nullptr)
	{
		al_destroy_bitmap(timeStat.bmp);
	}
	if (unitStat.bmp != nullptr)
	{
		al_destroy_bitmap(unitStat.bmp);
	}
	if (moneyStat.bmp != nullptr)
	{
		al_destroy_bitmap(moneyStat.bmp);
	}
	if (font != nullptr)
	{
		al_destroy_font(font);
	}
}

void gameStatus::setTime(unsigned int time)
{
	timeStat.value = time;
}

void gameStatus::setUnitCount(unsigned int unitCount)
{
	unitStat.value = unitCount;
}

void gameStatus::setMoney(unsigned int money)
{
	moneyStat.value = money;
}

void gameStatus::drawContent()
{
	int row = contentStartX, col = contentStartY;
	al_draw_bitmap(timeStat.bmp, row, col, 0);
	row += al_get_bitmap_width(timeStat.bmp);
	al_draw_textf(font, al_color_name(FONT_COLOR), row, col, 0, "%d", timeStat.value);
	row += (getDigitCount(timeStat.value) + 1) * al_get_text_width(font, "_");	//multiplico la cantidad de digitos por el ancho de un caracter en pixeles
	al_draw_bitmap(unitStat.bmp, row, col, 0);
	row += al_get_bitmap_width(unitStat.bmp);
	al_draw_textf(font, al_color_name(FONT_COLOR), row, col, 0, "%d", unitStat.value);
	row += getDigitCount(unitStat.value) * al_get_text_width(font, "_");
	al_draw_bitmap(moneyStat.bmp, row, col, 0);
	row += al_get_bitmap_width(moneyStat.bmp);
	al_draw_textf(font, al_color_name(FONT_COLOR), row, col, 0, "%d", moneyStat.value);

}

void gameStatus::resizeContent()
{
}

unsigned int getDigitCount(unsigned int n)
{
	return (((int)log10(n)) + 1);
}
