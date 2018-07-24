#include "pipBoy.h"

#include <iostream>
#include <vector>
#include <string>

#include "paths.h"

pipBoy::pipBoy(ALLEGRO_DISPLAY * display, std::vector<std::string> mapPaths)
	: contentBox(display, 0, 0, 1, 1)
{
	if (valid)
	{
		status = WELCOME;
		font = al_load_font(PIPBOY_FONT_NAME, -PIPBOY_FONT_SIZE, 0);
		if (font == nullptr)
		{
			valid = false;
			std::cout << "No se pudo cargar la font " << PIPBOY_FONT_NAME << ". No se puedo crear el pip-boy" << std::endl;
		}
		for(std::vector<std::string>::iterator it = mapPaths.begin(); it != mapPaths.end() && valid; it++)
		{
			ALLEGRO_BITMAP * mapBmp = getMapBmp(*it);
			if (mapBmp != nullptr)
			{
				mapBmps.push_back(mapBmp);
			}
		}
		currentMapBmp = mapBmps.begin();
	}
}

pipBoy::~pipBoy()
{
	al_destroy_font(font);
	for (std::vector<ALLEGRO_BITMAP *>::iterator it = mapBmps.begin(); it != mapBmps.end(); it++)
	{
		if ((*it) != nullptr)
		{
			al_destroy_bitmap(*it);
		}
	}
}

void pipBoy::setStatus(pipBoyStatus_t status)
{
	this->status = status;
}

pipBoyStatus_t pipBoy::getStatus()
{
	return status;
}

void pipBoy::setName(std::string name)
{
	this->name = name;
}

void pipBoy::setIP(std::string ip)
{
	this->ip = ip;
}

void pipBoy::nextMap()
{
	if (currentMapBmp != (mapBmps.end() - 1))
	{
		currentMapBmp++;
	}
}

void pipBoy::previousMap()
{
	if (currentMapBmp != mapBmps.begin())
	{
		currentMapBmp--;
	}
}

std::string pipBoy::getCurrentMapPath()
{
	return mapPaths[currentMapBmp - mapBmps.begin()];
}

ALLEGRO_BITMAP * pipBoy::getMapBmp(std::string mapPath)
{
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap(); //Hacer backup del bmp actual
	ALLEGRO_BITMAP * mapBmp = al_create_bitmap(contentWidth, contentHeight);
	al_set_target_bitmap(mapBmp);

	al_clear_to_color(al_map_rgb_f(0,0,0));
	al_draw_text(font, { (float)0.45, 1, 1, 1 }, 0, 0, 0, mapPath.c_str());	//TODO: hacer el bmp posta
	
	al_set_target_bitmap(backupBmp);

	return mapBmp;
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

	case CHOOSING_MAP:
		al_draw_bitmap((*currentMapBmp), contentStartX, contentStartY, 0);
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
