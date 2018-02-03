#include "simpleButton.h"

#include <iostream>

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include "paths.h"

#define FONT_NAME "PressStart2P.ttf"
#define DEFAULT_BG_COLOR "white"		//TODO: unificar palettes.
#define DEFAULT_FONT_COLOR "black"

#define BUTTON_CORNER_ROUNDNESS 10

#define PASS_TEXT "PASS"
#define BUY_TEXT "BUY"
#define CANCEL_TEXT "CANCEL"

using namespace std;

simpleButton::simpleButton(simpleButtonType_t simpleButonType, float leftX, float topY, float width, float height)
	: button(leftX, topY, width, height)
{
	if (valid)
	{
		this->simpleButtonType;
		float fontHeight = height;
		font = al_load_font(FONT_PATH FONT_NAME, -fontHeight, 0);
		if (font == nullptr)
		{
			cout << "No se pudo cargar la font " << FONT_PATH FONT_NAME << endl;
			valid = false;
			return;
		}

		switch (simpleButonType)
		{
		case PASS:
			text = string(PASS_TEXT);
			break;
		case BUY:
			text = string(BUY_TEXT);
			break;
		case CANCEL:
			text = string(CANCEL_TEXT);
			break;
		default:
			break;
		}

		//float textWidth = al_get_text_width(font, this->text.c_str());
		//if (textWidth > width)	//Si el texto no entra en el boton, cargar la font pero mas "apretada"
		//{
		//	al_destroy_font(font);
		//	font = al_load_font
		//}							//TODO: "achicar" la font si hace falta

		bgColor = al_color_name(DEFAULT_BG_COLOR);
		fontColor = al_color_name(DEFAULT_FONT_COLOR);
	}
}

simpleButton::~simpleButton()
{
	if (font != nullptr)
	{
		al_destroy_font(font);
	}
}

void simpleButton::draw()
{
	al_draw_filled_rounded_rectangle(leftX, topY, leftX + width, topY + height, 10, 10, bgColor);
	al_draw_text(font, fontColor, leftX + width / 2, topY, ALLEGRO_ALIGN_CENTER, text.c_str());
}

void simpleButton::setBgColor(ALLEGRO_COLOR bgColor)
{
	this->bgColor = bgColor;
}
