#pragma once
#include "contentBox.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>

typedef struct { ALLEGRO_BITMAP * bmp; unsigned int value; }stat_t;

//TODO: esta clase esta medio cabeza, le falta control del ancho del contenido.

class gameStatus :
	public contentBox
{
public:
	gameStatus(ALLEGRO_DISPLAY * display, float startX, float startY, 
		float width, float height, bool isBoxTransparent = false);
	void setTime(unsigned int time);
	void setUnitCount(unsigned int unitCount);
	void setMoney(unsigned int money);

	~gameStatus();
private:
	void drawContent();
	void resizeContent();
	stat_t timeStat;
	stat_t unitStat;
	stat_t moneyStat;
	ALLEGRO_FONT * font;
};

