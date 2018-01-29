#include "HPbar.h"
#include <iostream>

#include <allegro5\allegro_primitives.h>

#define RATIO(num, denom) ((float)(num) / (float)(denom))

using namespace std;


HPbar::HPbar(float leftX, float topY, float width, float height,
		unsigned int maxHP, hpBarPalette_t palette, bool emptyFromRight)
{
	if (!width || !height || !maxHP)
	{
		cout << "Valor invalido ingresado al constructor de HPbar (width, height y maxHP no pueden ser nulos)" << endl;
		valid = false;
	}
	else
	{
		valid = true;
		this->width = width;
		this->height = height;
		this->leftX = leftX;
		this->topY = topY;
		this->currentHP = this->maxHP = maxHP;
		this->palette = palette;
		this->emptyFromRight = emptyFromRight;
	}
}

HPbar::~HPbar()
{
}

void HPbar::draw()
{
	//fondo
	al_draw_filled_rectangle(leftX, topY, leftX + width, topY + height, palette.background);

	al_flip_display();

	//HP
	if(emptyFromRight)
	{
		al_draw_filled_rectangle(leftX, topY, leftX + RATIO(currentHP, maxHP) * width, topY + height, palette.hp);
	}
	else
	{
		al_draw_filled_rectangle(leftX + (1 - RATIO(currentHP, maxHP)) * width, topY, leftX + width, topY + height, palette.hp);
	}

	//frame
	al_draw_rounded_rectangle(leftX, topY, leftX + width, topY + height, 5, 5, palette.frameBase, 5);	//TODO: sacar magic number
}

bool HPbar::isValid()
{
	return valid;
}

unsigned int HPbar::getWidth()
{
	return width;
}

unsigned int HPbar::getHeight()
{
	return height;
}

void HPbar::setWidth(int width)
{
	this->width = width;
}

void HPbar::setHeight(int height)
{
	this->height = height;
}

int HPbar::getCurrentHP()
{
	return currentHP;
}

void HPbar::setCurrentHP(int currentHP)
{
	this->currentHP = currentHP;
}

int HPbar::changeHPby(signed int HPchange)
{
	currentHP += HPchange;
	if (currentHP > maxHP)
	{
		currentHP = maxHP;
	}
	else if (currentHP < 0)
	{
		currentHP = 0;
	}
	return currentHP;
}

void HPbar::setPosition(unsigned int leftX, unsigned int topY)
{
	this->topY = topY;	
	this->leftX = leftX;
}

void HPbar::setPalette(hpBarPalette_t palette)
{
	this->palette = palette;
}

bool HPbar::getTransparency()
{
	return transparency;
}

void HPbar::setTransparency(bool transparency)
{
	this->transparency = transparency;
}
