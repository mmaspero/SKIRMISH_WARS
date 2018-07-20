#include "pipBoy.h"

#include <iostream>

#include "paths.h"

pipBoy::pipBoy(ALLEGRO_DISPLAY * display) : contentBox(display, 0, 0, 1, 1)
{
	if (valid)
	{
		status = WELCOME;
		font = al_load_font(FONT_PATH PIPBOY_FONT_NAME, -PIPBOY_FONT_SIZE, 0);
		if (font == nullptr)
		{
			valid = false;
			std::cout << "No se puso cargar la font " << PIPBOY_FONT_NAME << ". No se puedo crear el pip-boy" << std::endl;
		}
	}
}

pipBoy::~pipBoy()
{
	al_destroy_font(font);
}

void pipBoy::setStatus(pipBoyStatus_t status)
{
	this->status = status;
}

void pipBoy::setName(std::string name)
{
	this->name = name;
}

void pipBoy::setIP(std::string ip)
{
	this->ip = ip;
}

void pipBoy::drawContent()
{
	switch (status)
	{
	case WELCOME:
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY, ALLEGRO_ALIGN_CENTER, PIPBOY_WELCOME_MSG_LINE_1);
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY + PIPBOY_FONT_SIZE, ALLEGRO_ALIGN_CENTER, PIPBOY_WELCOME_MSG_LINE_2);

		break;

	case INSERTING_NAME:
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY, ALLEGRO_ALIGN_CENTER, PIPBOY_INSERTING_NAME_MSG);
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY + PIPBOY_FONT_SIZE, ALLEGRO_ALIGN_CENTER, name.c_str());
		break;

	case TRYING_IP:
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY, ALLEGRO_ALIGN_CENTER, PIPBOY_TRYING_IP_MSG);
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY + PIPBOY_FONT_SIZE, ALLEGRO_ALIGN_CENTER, ip.c_str());
		break;

	case RETRYING_IP:
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY, ALLEGRO_ALIGN_CENTER, PIPBOY_RETRYING_IP_MSG);
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY + PIPBOY_FONT_SIZE, ALLEGRO_ALIGN_CENTER, ip.c_str());
		break;

	case WAITING_CONNECTION:
		al_draw_text(font, PIPBOY_FONT_COLOR, contentStartX + contentWidth / 2, contentStartY, ALLEGRO_ALIGN_CENTER, PIPBOY_CONNECTION_MSG);
		break;

	default:
		break;
	}
}

void pipBoy::resizeContent()
{
}