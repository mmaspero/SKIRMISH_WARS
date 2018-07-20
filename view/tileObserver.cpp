#include "tileObserver.h"

#include <iostream>

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include "paths.h"

#define GRASS_TEXTURE "grassTexture.png"
#define RIVER_TEXTURE "riverTexture.png"
#define ROAD_TEXTURE  "roadTexture.png"
#define FOREST_TEXTURE "forestTexture.jpg"
#define HILL_TEXTURE "hillTexture.png"

#define FOG_COLOR "hotpink"

#define ANTIAIR_SPRITE_R		SPRITE_PATH "antiair_r.png"
#define APC_SPRITE_R			SPRITE_PATH "apc_r.png"
#define ARTILLERY_SPRITE_R		SPRITE_PATH "artillery_r.png"
#define INFANTRY_SPRITE_R		SPRITE_PATH "infantry_r.png"
#define MECH_SPRITE_R			SPRITE_PATH	"mech_r.png"
#define MEDTANK_SPRITE_R		SPRITE_PATH "medtank_r.png"
#define RECON_SPRITE_R			SPRITE_PATH "recon_r.png"
#define ROCKET_SPRITE_R			SPRITE_PATH "rocket_r.png"
#define TANK_SPRITE_R			SPRITE_PATH "tank_r.png"


#define ANTIAIR_SPRITE_B		SPRITE_PATH "antiair_b.png"
#define APC_SPRITE_B			SPRITE_PATH "apc_b.png"
#define ARTILLERY_SPRITE_B		SPRITE_PATH "artillery_b.png"
#define INFANTRY_SPRITE_B		SPRITE_PATH "infantry_b.png"
#define MECH_SPRITE_B			SPRITE_PATH	"mech_b.png"
#define MEDTANK_SPRITE_B		SPRITE_PATH "medtank_b.png"
#define RECON_SPRITE_B			SPRITE_PATH "recon_b.png"
#define ROCKET_SPRITE_B			SPRITE_PATH "rocket_b.png"
#define TANK_SPRITE_B			SPRITE_PATH "tank_b.png"

using namespace std;

tileObserver::tileObserver(Tile * t, tileButton * tButton, toolbox * tBox)
{
	this->t = t;
	this->tBox = tBox;
	this->tButton = tButton;

	if (t && tBox && tButton)
	{
		valid = true;	//Si ninguno de los punteros es nullptr.
	}
	else
	{
		valid = false;
	}
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

	if (t->status == FOG)
	{
		al_clear_to_color(al_color_name(FOG_COLOR));	//TODO: sacar magic number
	}
	else
	{
		terrain_t terrainType = t->t;
		unit_t unitType;
		basicUnitType_t unitBasicType;
		if (t->hasUnit())
		{
			unitType = t->u->getType();
			unitBasicType = t->u->getBasicType();
		}
		tileStatus_t tileStatus = t->status;

		ALLEGRO_BITMAP * terrainBmp = nullptr;
		ALLEGRO_BITMAP * unitBmp = nullptr;
		ALLEGRO_BITMAP * unitBasicTypeBmp = nullptr;
		ALLEGRO_BITMAP * tileStatusBmp = nullptr;
		ALLEGRO_COLOR marginColor;

		ALLEGRO_COLOR tc;;	//En caso de que no se pueda cargar un bitmap del terreno, se pinta el fondo del bitmap de un color que lo represente
		switch (terrainType)
		{
		case GRASS:
			terrainBmp = al_load_bitmap(IMAGE_PATH GRASS_TEXTURE);
			if(terrainBmp == nullptr)
			{
				tc = al_color_name("green");
				cout << "No se pudo cargar el bitmap de textura de pasto " << IMAGE_PATH GRASS_TEXTURE << endl;
			}
			break;
		case RIVER:
			terrainBmp = al_load_bitmap(IMAGE_PATH RIVER_TEXTURE);
			if (terrainBmp == nullptr)
			{
				tc = al_color_name("blue");
				cout << "No se pudo cargar el bitmap de textura de rio " << IMAGE_PATH RIVER_TEXTURE << endl;
			}
			break;
		case ROAD:
			terrainBmp = al_load_bitmap(IMAGE_PATH ROAD_TEXTURE);
			if (terrainBmp == nullptr)
			{
				tc = al_color_name("grey");
				cout << "No se pudo cargar el bitmap de textura de calle " << IMAGE_PATH ROAD_TEXTURE << endl;
			}
			break;
		case FOREST:
			terrainBmp = al_load_bitmap(IMAGE_PATH FOREST_TEXTURE);
			if (terrainBmp == nullptr)
			{
				tc = al_color_name("dark green");
				cout << "No se pudo cargar el bitmap de textura del bosque " << IMAGE_PATH FOREST_TEXTURE << endl;
			}
			break;
		case HILL:
			terrainBmp = al_load_bitmap(IMAGE_PATH HILL_TEXTURE);
			tc = al_color_name("blue");
			if (terrainBmp == nullptr)
			{
				tc = al_color_name("light blue");
				cout << "No se pudo cargar el bitmap de textura de la colina " << IMAGE_PATH HILL_TEXTURE << endl;
			}
			break;
		default:
			break;
		}

		//Cargar bitmap de la unidad presente
		if (t->hasUnit())
		{
			switch (t->getUnit()->getType())
			{
			case RECON: 
			{ 
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? RECON_SPRITE_R : RECON_SPRITE_B); 
			} 
			break;
			case ROCKET: 
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? ROCKET_SPRITE_R : ROCKET_SPRITE_B);
			}
			break;
			case MECH:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? MECH_SPRITE_R : MECH_SPRITE_B);
			}
			break;
			case INFANTRY:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? INFANTRY_SPRITE_R : INFANTRY_SPRITE_B);
			}
			break;
			case TANK: 
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? TANK_SPRITE_R : TANK_SPRITE_B);
			}
		    break;
			case ARTILLERY:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? ARTILLERY_SPRITE_R : ARTILLERY_SPRITE_B);
			}
			break;
			case ANTIAIR:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? ANTIAIR_SPRITE_R : ANTIAIR_SPRITE_B);
			}
			break;
			case APC:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? APC_SPRITE_R : APC_SPRITE_B);
			}
			break;
			case MEDTANK:
			{
				unitBmp = al_load_bitmap(t->getUnit()->getPlayer() == USER ? MEDTANK_SPRITE_R : MEDTANK_SPRITE_B);
			}
			break;
			}
			switch (unitBasicType);
		}

		std::string name2;
		//TODO: sacar a la mierda
		if (t->hasBuilding())
		{
			switch (t->b->getType())
			{
			case HEADQUARTERS:
				name2 = "HQ";
				break;
			case FACTORY:
				name2 = "FACT";
				break;
			case CITY:
				name2 = "CITY";
				break;
			}
		}


		switch (tileStatus)
		{
		case SELECTED:		//TODO: cambiar 
			marginColor = al_map_rgb_f(0, 1, 0);
			break;
		case CAN_ATTACK:
			marginColor = al_map_rgb_f(1, 0, 0);
			break;
		case CAN_MOVE:
			marginColor = al_map_rgb_f(1, 1, 0);
			break;
		case VISIBLE: default:
			marginColor = al_map_rgba_f(0, 0, 0, 0);	//no se ve ningun margen
			break;
		}

		if (terrainBmp != nullptr)
		{
			al_draw_scaled_bitmap(terrainBmp, 0, 0, al_get_bitmap_width(terrainBmp), al_get_bitmap_height(terrainBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(terrainBmp);
		}
		else 
		{
			al_clear_to_color(tc);
		}

		if (unitBmp != nullptr)
		{
			al_draw_scaled_bitmap(unitBmp, 0, 0, al_get_bitmap_width(unitBmp), al_get_bitmap_height(unitBmp),
				0, 0, bmpW, bmpH, 0);
			al_destroy_bitmap(unitBmp);
		}
		{
			ALLEGRO_FONT * font = al_load_font(FONT_PATH "ttf.ttf", -bmpH / 2, 0);
			{
				if (font == nullptr)
				{
					cout << "malu sus alta gilastra y no se cargo la font " << FONT_PATH << "ttf.ttf" << endl;
					return;
				}
				else
				{
					al_draw_text(font, al_color_name("white"), 0, bmpH / 2.0, 0, name2.c_str());
					al_destroy_font(font);
				}
			}
		}
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
			al_destroy_bitmap(tileStatusBmp);
		}

		al_draw_rectangle(0, 0, bmpW, bmpH, marginColor, 5);	//TODO: sacar magic numbers
		//TODO: agregar la vida
	}

	tButton->setUnformattedBmp(buttonBmp);
	al_set_target_bitmap(backupBmp);
	
	tButton->draw();
	al_flip_display();	//TODO: sacar!!!!! hacer como contentBox con el set clipping rectangle y la herencia y bla bla bla

}