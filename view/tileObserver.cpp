#include "tileObserver.h"

#include <iostream>

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include "paths.h"

using namespace std;

tileObserver::tileObserver(Tile * t, tileButton * tButton, toolbox * tBox)
{
	this->t = t;
	this->tBox = tBox;
	this->tButton = tButton;
}


tileObserver::~tileObserver()
{
}


void tileObserver::update()
{
	int bmpW = tButton->getWidth(), bmpH = tButton->getHeight();

	ALLEGRO_BITMAP * buttonBmp = al_create_bitmap(bmpW, bmpH);
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
	al_set_target_bitmap(buttonBmp);

	if (t->status = FOG)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));	//TODO: sacar magic number
	}
	else
	{
		terrain_t terrainType = t->t;
		unit_t unitType = t->u->getType();
		unitType_t unitBasicType = t->u->getBasicType();
		tileStatus_t tileStatus = t->status;

		ALLEGRO_BITMAP * terrainBmp = nullptr;
		ALLEGRO_BITMAP * unitBmp = nullptr;
		ALLEGRO_BITMAP * unitBasicTypeBmp = nullptr;
		ALLEGRO_BITMAP * tileStatusBmp = nullptr;
		ALLEGRO_COLOR marginColor;

		ALLEGRO_COLOR tc;
		switch (terrainType)
		{
		case GRASS:
			tc = al_color_name("green");
			//terrainBmp = al_load_bitmap( el del terreno);
			break;
		case RIVER:
			tc = al_color_name("blue");
			//terrainBmp = al_load_bitmap( el del terreno);
			break;
		case ROAD:
			tc = al_color_name("grey");
			//terrainBmp = al_load_bitmap( el del terreno);
			break;
		case FOREST:
			tc = al_color_name("darkgreen");
			//terrainBmp = al_load_bitmap( el del terreno);
			break;
		case HILL:
			tc = al_color_name("yellow");			
			//terrainBmp = al_load_bitmap( el del terreno);
			break;
		default:
			break;
		}

		std::string name;
		if (t->hasUnit())
		{
			switch (t->getUnit()->getType()) {
			case RECON: { name = RE_STR; }		break;	//unitBmp = al_load_bitmap(fjhfkjskdj)
			case ROCKET: { name = RO_STR; }		break;
			case MECH: { name = ME_STR; }		break;
			case INFANTRY: { name = IN_STR; }	break;
			case TANK: { name = TA_STR; }		break;
			case ARTILLERY: { name = AR_STR; }	break;
			case ANTIAIR: { name = AA_STR; }		break;
			case APC: { name = AP_STR; }			break;
			case MEDTANK: { name = MT_STR; }		break;
			}
		}


		switch (unitBasicType);

		switch (tileStatus)
		{
		case SELECTED:		//TODO: cambiar 
			marginColor = al_map_rgb_f(0, 1, 0);
			break;
		case CAN_ATTACK:
			marginColor = al_map_rgb_f(1, 0, 0);
			break;
		case CAN_MOVE:
			marginColor = al_map_rgb(1, 1, 0);
			break;
		case VISIBLE:
			marginColor = al_map_rgba_f(0, 0, 0, 0);	//no se ve ningun margen
			break;
		}

		if (terrainBmp != nullptr)
		{
			al_draw_scaled_bitmap(terrainBmp, 0, 0, al_get_bitmap_width(terrainBmp), al_get_bitmap_height(terrainBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(terrainBmp);
		}
		al_clear_to_color(tc);
		if (unitBmp != nullptr)
		{
			al_draw_scaled_bitmap(unitBmp, 0, 0, al_get_bitmap_width(unitBmp), al_get_bitmap_height(unitBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(terrainBmp);
		}
		{ALLEGRO_FONT * font = al_load_font(FONT_PATH "ttf.ttf", -bmpH / 4, 0);
		{
			if (font == nullptr)
			{
				cout << "malu sus alta gilastra y no se cargo la font " << FONT_PATH << "ttf.ttf" << endl;
				return;
			}
			else
			{
				al_draw_text(font, al_color_name("hot pink"), 0, 0, 0, name.c_str());
				al_destroy_font(font);
			}
		}}
		if (unitBasicTypeBmp != nullptr)
		{
			al_draw_scaled_bitmap(unitBasicTypeBmp, 0, 0, al_get_bitmap_width(unitBasicTypeBmp), al_get_bitmap_height(unitBasicTypeBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(terrainBmp);
		}
		if (tileStatusBmp != nullptr)
		{
			al_draw_scaled_bitmap(tileStatusBmp, 0, 0, al_get_bitmap_width(tileStatusBmp), al_get_bitmap_height(tileStatusBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(terrainBmp);
		}

		al_draw_rectangle(0, 0, bmpW, bmpH, marginColor, 5);	//TODO: sacar magic numbers
		//TODO: agregar la vida
	}

	tButton->setUnformattedBmp(buttonBmp);
	al_set_target_bitmap(backupBmp);
	
}