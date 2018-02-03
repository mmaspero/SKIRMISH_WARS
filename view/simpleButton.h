#pragma once
#include "button.h"

#include <string>

#include <allegro5\allegro_font.h>

class simpleButton :
	public button
{
public:
	simpleButton(simpleButtonType_t simpleButtonType, float leftX, float topY, float width, float height);
	~simpleButton();

	virtual void draw();
	void setBgColor(ALLEGRO_COLOR bgColor);

private:
	simpleButtonType_t simpleButtonType;
	std::string text;
	ALLEGRO_FONT * font;
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR fontColor;
};

