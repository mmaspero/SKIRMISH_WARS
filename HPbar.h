#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <string>

struct hpBarPalette_t {
	ALLEGRO_COLOR hp;
	ALLEGRO_COLOR background;
	ALLEGRO_COLOR frameBase;
	ALLEGRO_COLOR frameHighlight;
};

class HPbar
{
public:
	HPbar(float leftX, float topY, float width, float height,
		unsigned int maxHP,  hpBarPalette_t palette, bool emptyFromRight);
	//max height es width/4 
	~HPbar();
	void draw();
	bool isValid();
	unsigned int getWidth();
	unsigned int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	int getCurrentHP();
	void setCurrentHP(int currentHP);
	int changeHPby(signed int HPchange);
	void setPosition(unsigned int leftX, unsigned int topY);
	void setPalette(hpBarPalette_t palette);
	bool getTransparency();
	void setTransparency(bool transparency);
private:
	bool valid;
	unsigned int width;
	unsigned int height;
	unsigned int leftX;
	unsigned int topY;
	unsigned int maxHP;
	int currentHP;
	hpBarPalette_t palette;
	bool emptyFromRight;
	bool transparency;	//TODO: documentar
};
