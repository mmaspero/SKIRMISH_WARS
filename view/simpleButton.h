#pragma once
#include "button.h"

#include <string>

#include <allegro5\allegro_font.h>

typedef enum { PASS_BUTTON, STORE_BUTTON, BUY_BUTTON, CANCEL_BUTTON, BACK_BUTTON, SIMPLE_BUTTON_TYPES_N } simpleButtonType_t;	//botones que son solo una palabra y no hacen nada magico. Other quiere decir que no es niguno de los que ya estan estipulados


class simpleButton :
	public button
{
public:
	simpleButton(simpleButtonType_t simpleButtonType, float leftX, float topY, float width, float height);
	~simpleButton();

	virtual void draw();
	void setBgColor(ALLEGRO_COLOR bgColor);
	simpleButtonType_t getSimpleType();

	bool isItPass();
	bool isItBuy();
	bool isItCancel();
	bool isItBack();
	bool isItStore();
	bool isItThisSimpleType(simpleButtonType_t simpleType);

private:
	simpleButtonType_t simpleType;
	std::string text;
	ALLEGRO_FONT * font;
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR fontColor;


};

