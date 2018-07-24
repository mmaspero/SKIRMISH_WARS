#include "productButton.h"

#include "config\sprite_config.h"

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "drawingFunctions.h"
#include "paths.h"


#define	CONFIG_FILE "productButton.cfg"



#define FONT_NAME "Minecraft.ttf"
#define	BIG_FONT_SIZE    30

#define BUTTON_MARGIN(w, h) (((w)>(h) ? h : w) / 20.0)
#define BUTTON_CORNER_ROUNDNESS 10

#define COIN_HEIGHT_IN_MARGINS 6	//La moneda que indica plata tiene COIN_HEIGHT_IN_MARGIN veces la altura del margen
#define LOGO_SIDE_IN_MARGINS 7

#define COIN_IMG "coin.png"

#define ANTIAIR_NAME "ANTIAIR"

#define TREAD_LOGO_BMP IMAGE_PATH "tread_logo.png"
#define FOOT_LOGO_BMP TREAD_LOGO_BMP
#define WHEEL_LOGO_BMP TREAD_LOGO_BMP


using namespace std;

productButton::productButton(float rLeftX, float rTopY, float rWidth, float rHeight,
	float eLeftX, float eTopY, float eWidth, float eHeight, unit_t unitSpecificType)
	: button(rLeftX, rTopY, rWidth, rHeight)
{
	if (valid)	//Proseguir solo si construyo button sin problemas
	{
		buttonType = PRODUCT_BUTTON;

		resizedBmp = nullptr;	//NO SE USA!!! EN CAMBIO SE USA reducedBmp y expandedBmp

		reducedBmp = nullptr;
		expandedBmp = nullptr;
								//TODO: validacion de parametros
		this->rLeftX = rLeftX;
		this->rTopY = rTopY;
		this->rWidth = rWidth;
		this->rHeight = rHeight;

		this->eLeftX = eLeftX;
		this->eTopY = eTopY;
		this->eWidth = eWidth;
		this->eHeight = eHeight;

		this->unitSpecificType = unitSpecificType;

		switch (unitSpecificType)
		{
		case RECON:
			unformattedBmp = al_load_bitmap(RECON_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << RECON_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case ROCKET:
			unformattedBmp = al_load_bitmap(ROCKET_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << ROCKET_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case MECH:
			unformattedBmp = al_load_bitmap(MECH_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << MECH_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case INFANTRY:
			unformattedBmp = al_load_bitmap(INFANTRY_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << INFANTRY_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case TANK:
			unformattedBmp = al_load_bitmap(TANK_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << TANK_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case ARTILLERY:
			unformattedBmp = al_load_bitmap(ARTILLERY_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << ARTILLERY_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case ANTIAIR:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << ANTIAIR_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case APC:
			unformattedBmp = al_load_bitmap(APC_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << APC_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		case MEDTANK:
			unformattedBmp = al_load_bitmap(MEDTANK_SPRITE_R);
			if (unformattedBmp == nullptr)
			{
				cout << "No se pudo cargar el sprite " << MEDTANK_SPRITE_R << endl;
				valid = false;
				return;
			}
			break;
		default:
			break;
		}

		margin = BUTTON_MARGIN(rWidth, rHeight);	//definir el margen con las dimensiones del boton reducido


		calculateCurrentDimensions();
		setExpandedBmp();
		setReducedBmp();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

productButton::~productButton()
{
	if (unformattedBmp != nullptr)
		al_destroy_bitmap(unformattedBmp);
	if (resizedBmp != nullptr)
		al_destroy_bitmap(resizedBmp);
	if (reducedBmp != nullptr)
		al_destroy_bitmap(reducedBmp);
	if (expandedBmp != nullptr)
		al_destroy_bitmap(expandedBmp);
}

bool productButton::getCanBuy()
{
//	return canBuy;
	return true;
}

void productButton::setCanBuy(bool canBuy)
{
//	this->canBuy = canBuy;
}

unit_t productButton::getUnitSpecificType()
{
	return unitSpecificType;
}

void productButton::draw()
{
	if (!hidden)
	{
		ALLEGRO_BITMAP * auxBmp = nullptr;
		if (selected)
		{
			auxBmp = expandedBmp;
		}
		else
		{
			auxBmp = reducedBmp;
		}
		if (auxBmp != nullptr)
		{
			al_draw_bitmap(auxBmp, leftX, topY, 0);
			al_flip_display();	//TODO: esta bien que haga un flip de todo el display?
		}
	}
}

void productButton::selectedOn()
{
	selected = true;
	calculateCurrentDimensions();
}

void productButton::selectedOff()
{
	selected = false;
	calculateCurrentDimensions();
}

void productButton::toggleSelected()
{
	if (selected) 
	{
		selectedOff();
	}
	else
	{
		selectedOn();
	}
}

void productButton::setSelected(bool selected)
{
	if (selected)
	{
		selectedOn();
	}
	else
	{
		selectedOff();
	}
}

void productButton::hiddenOn()
{
	hidden = true;
}

void productButton::hiddenOff()
{
	hidden = false;
}

void productButton::toggleHidden()
{
	hidden = !hidden;
}

void productButton::setHidden(bool hidden)
{
	this->hidden = hidden;
}

bool productButton::isHidden()
{
	return hidden;
}

bool productButton::setReducedBmp()
{

	basicUnitType_t unitBasicType;
	bool canBuy;
	unsigned int cost;
	unsigned int firepower[N_BASIC_U_TYPES];	//Cuantos HP le saca a cada tipo basico de unidad
	unsigned int firepowerReduced[N_BASIC_U_TYPES];
	unsigned int movingPoints[N_TERRAINS];



	//TODO: copiar toda la info necesaria y borrar lo de abajo
	cost = Unit::getCost(unitSpecificType);
	for (int i = 0; i < N_BASIC_U_TYPES; i++)	//Cuantos HP le saca a cada tipo basico de unidad
	{
		firepower[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, false);
		firepowerReduced[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, true);
	}
	for (int i = 0; i < N_TERRAINS; i++)
	{
		movingPoints[i] = Unit::getTerrainMod(unitSpecificType, (terrain_t)i);
	}


	//TODO: sacarlo de una funcion de Unit::
	if (FIRST_W <= unitSpecificType && unitSpecificType < FIRST_F)
		unitBasicType = WHEEL;

	else if (FIRST_F <= unitSpecificType && unitSpecificType < FIRST_T)
		unitBasicType = FOOT;

	else if (FIRST_T <= unitSpecificType && unitSpecificType < N_UNIT_TYPES)
		unitBasicType = TREAD;

	//Cargo el color de fondo y el logo del basicType
	switch (unitBasicType)
	{
	case WHEEL:
		bgColor = al_color_name(WHEEL_BG_COLOR);
		basicTypeLogo = al_load_bitmap(WHEEL_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de wheel" << endl;
			valid = false;
		}
		break;
	case TREAD:
		bgColor = al_color_name(TREAD_BG_COLOR);
		basicTypeLogo = al_load_bitmap(TREAD_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de tread" << endl;
			valid = false;
		}
		break;
	case FOOT:
		bgColor = al_color_name(FOOT_BG_COLOR);
		basicTypeLogo = al_load_bitmap(FOOT_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de foot" << endl;
			valid = false;
		}
		break;
	default:	//TODO: ???
		break;
	}



	if (reducedBmp != nullptr)
	{
		al_destroy_bitmap(reducedBmp);
	}
	reducedBmp = al_create_bitmap(width, height);

	//hacer backup del target bitmap actual y dibujar el boton en resizedBmp
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
	al_set_target_bitmap(reducedBmp);

	//Dibujar fondo
	al_draw_filled_rounded_rectangle(margin, margin,
		width - margin, height - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		bgColor);

	//TODO: y si unformattedBmp = nullptr?
	if (unformattedBmp != nullptr)
	{
		//Dibujar la unidad
		al_draw_scaled_bitmap(unformattedBmp,
			0,										0,
			al_get_bitmap_width(unformattedBmp),	al_get_bitmap_height(unformattedBmp),
			margin * 2,								margin * 2,
			width - margin * 2 * 2,					height - margin * 2 * 2,
			0);	//TODO: sacar magic numbers
	}

	//Dibujar borde
	al_draw_rounded_rectangle(margin, margin,
		width - margin, height - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		{ 0.7f, 0.7f, 0.7f, 1 }, 6);	//TODO: sacar magic numbers

	//Dibujar el logo del basic type con el tamanio adecuado y luego eliminar
	al_draw_scaled_bitmap(basicTypeLogo,
		0,										0,
		al_get_bitmap_width(basicTypeLogo),		al_get_bitmap_height(basicTypeLogo),
		width - margin * LOGO_SIDE_IN_MARGINS,	height - margin * LOGO_SIDE_IN_MARGINS,
		margin * LOGO_SIDE_IN_MARGINS,			margin * LOGO_SIDE_IN_MARGINS, 0);

	//Cargar imagen de la moneda
	ALLEGRO_BITMAP * auxBmp = al_load_bitmap(IMAGE_PATH COIN_IMG);	//TODO: sacar de define
	if (auxBmp == nullptr)
	{
		cout << "No se pudo cargar la imagen de moneda" << endl;
		if (reducedBmp != nullptr)
		{
			al_destroy_bitmap(reducedBmp);
		}
		al_set_target_bitmap(backupBmp);
		return false;	
	}

	//Dibujar moneda
	al_draw_scaled_bitmap(auxBmp,
		0,									0,
		al_get_bitmap_width(auxBmp),		al_get_bitmap_height(auxBmp),
		0,									width - COIN_HEIGHT_IN_MARGINS * margin,
		COIN_HEIGHT_IN_MARGINS * margin,	COIN_HEIGHT_IN_MARGINS * margin,
		0);

	ALLEGRO_FONT * font = al_load_font(FONT_PATH FONT_NAME, - margin * COIN_HEIGHT_IN_MARGINS, 0);
	if (font == nullptr)
	{
		cout << "No se pudo cargar la font para el reduced Bmp" FONT_PATH FONT_NAME << endl;;
		if (reducedBmp != nullptr)
		{
			al_destroy_bitmap(reducedBmp);
		}
		if (auxBmp != nullptr)
		{
			al_destroy_bitmap(auxBmp);
		}
		al_set_target_bitmap(backupBmp);
		return false;
	}

	//Dibujar el precio
	al_draw_textf(font, al_color_name("white"), COIN_HEIGHT_IN_MARGINS * margin,
		height - COIN_HEIGHT_IN_MARGINS * margin / 2.0 - al_get_font_line_height(font) / 2.0,	//centrar verticalmente
		0, "%d", cost);
	//TODO: sacar, es solo de debug
	al_draw_textf(font, al_color_name("white"), 0, 0, 0, "%d", unitSpecificType);

	if (auxBmp != nullptr)
	{
		al_destroy_bitmap(auxBmp);
	}
	if (font != nullptr)
	{
		al_destroy_font(font);
	}

	al_set_target_bitmap(backupBmp);

	return true;
}

bool productButton::setExpandedBmp()
{

	basicUnitType_t unitBasicType;
	bool canBuy;		//TODO: como hago el canBuy?
	unsigned int cost;
	unsigned int firepower[N_BASIC_U_TYPES];	//Cuantos HP le saca a cada tipo basico de unidad
	unsigned int firepowerReduced[N_BASIC_U_TYPES];
	unsigned int movingPoints[N_TERRAINS];



	//TODO: copiar toda la info necesaria y borrar lo de abajo
	cost = Unit::getCost(unitSpecificType);
	for (int i = 0; i < N_BASIC_U_TYPES; i++)	//Cuantos HP le saca a cada tipo basico de unidad
	{
		firepower[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, false);
		firepowerReduced[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, true);
	}
	for (int i = 0; i < N_TERRAINS; i++)
	{
		movingPoints[i] = Unit::getTerrainMod(unitSpecificType, (terrain_t)i);
	}


	//TODO: sacarlo de una funcion de Unit::
	if (FIRST_W <= unitSpecificType && unitSpecificType < FIRST_F)
		unitBasicType = WHEEL;

	else if (FIRST_F <= unitSpecificType && unitSpecificType < FIRST_T)
		unitBasicType = FOOT;

	else if (FIRST_T <= unitSpecificType && unitSpecificType < N_UNIT_TYPES)
		unitBasicType = TREAD;

	//Cargo el color de fondo y el logo del basicType
	switch (unitBasicType)
	{
	case WHEEL:
		bgColor = al_color_name(WHEEL_BG_COLOR);
		basicTypeLogo = al_load_bitmap(WHEEL_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de wheel" << endl;
			valid = false;
		}
		break;
	case TREAD:
		bgColor = al_color_name(TREAD_BG_COLOR);
		basicTypeLogo = al_load_bitmap(TREAD_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de tread" << endl;
			valid = false;
		}
		break;
	case FOOT:
		bgColor = al_color_name(FOOT_BG_COLOR);
		basicTypeLogo = al_load_bitmap(FOOT_LOGO_BMP);
		if (basicTypeLogo == nullptr)
		{
			cout << "No se cargo el logo de foot" << endl;
			valid = false;
		}
		break;
	default:	//TODO: ???
		break;
	}







	if (expandedBmp != nullptr)
	{
		al_destroy_bitmap(expandedBmp);
	}
	expandedBmp = al_create_bitmap(eWidth, eHeight);

	//hacer backup del target bitmap actual y dibujar el boton en expandedBmp
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
	al_set_target_bitmap(expandedBmp);



	al_draw_filled_rounded_rectangle(margin, margin,
		eWidth - margin, eHeight - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		bgColor);	//Sacar el define de WHEEL COLOR y hacerlo para todos los basic types
	al_draw_scaled_bitmap(unformattedBmp, 0, 0,
		al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
		margin * 2, margin * 2,
		eHeight / 3.0 - margin * 2, eHeight / 3.0 - margin * 2,
		0);

	float smallFontHeight = eHeight / 15.0;	//TODO: sacar magic number
	ALLEGRO_FONT * smallFont = al_load_font(FONT_PATH FONT_NAME, -smallFontHeight, 0);
	if (smallFont == nullptr)
	{
		cout << "No se pudo crear el bitmap expandido del productButton de la unidad de tipo" << \
			unitSpecificType << "porque no se pudo cargar la font " << FONT_PATH FONT_NAME << endl;
	}

	al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, eHeight / 3.0, 0, "FIREPOWER");	//TODO: sacar magic numbers
	al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, eHeight / 3.0 + 2 * smallFontHeight, 0, "REDUCED FIREPOWER");
	al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, eHeight / 3.0 + 4 * smallFontHeight, 0, "TERRAIN MOV COST");	//TODO: no me entra la palabra completa 

	float fpSpacing = eWidth / N_BASIC_U_TYPES;	//Distancia entre los valores para firepower
	float fpX = fpSpacing / 2.0;		//Donde escribo el fp (centrado)
	for (int i = 0; i<N_BASIC_U_TYPES; i++)
	{
		al_draw_textf(smallFont, { 1,1,1,1 }, fpX, eHeight / 3.0 + smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", firepower[i]);
		al_draw_textf(smallFont, { 1,1,1,1 }, fpX, eHeight / 3.0 + 3 * smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", firepowerReduced[i]);
		fpX += fpSpacing;
	}
	float mpSpacing = eWidth / N_TERRAINS;	//Distancia entre los valores para movingPoints
	float mpX = mpSpacing / 2.0;		//Donde escribo el mp (centrado)
	for (int i = 0; i<N_TERRAINS; i++)
	{
		al_draw_textf(smallFont, { 1,1,1,1 }, mpX, eHeight / 3.0 + 5 * smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", movingPoints[i]);
		mpX += mpSpacing;
	}

	if (smallFont != nullptr)
	{
		al_destroy_font(smallFont);
	}
	al_set_target_bitmap(backupBmp);

	return true;
}

void productButton::setReducedLeftX(float rLeftX)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setReducedTopY(float rTopY)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setReducedWidth(float rWidth)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setReducedHeight(float rHeight)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setReducedDimensions(float rLeftX, float rTopY, float rWidth, float rHeight)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::getReducedDimensions(float * rLeftX, float * rTopY, float * rWidth, float * rHeight)
{
	*rLeftX = this->rLeftX;
	*rTopY = this->rTopY;
	*rWidth = this->rWidth;
	*rHeight = this->rHeight;
}

void productButton::setExpandedLeftX(float eLeftX)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setExpandedTopY(float eTopY)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setExpandedWidth(float eWidth)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setExpandedHeight(float eHeight)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setExpandedDimensions(float eLeftX, float eTopY, float eWidth, float eHeight)
{
	setAllDimensions(rLeftX, rTopY, rWidth, rHeight, eLeftX, eTopY, eWidth, eHeight);
}

void productButton::getExpandedDimensions(float * eLeftX, float * eTopY, float * eWidth, float * eHeight)
{
	*eLeftX = this->eLeftX;
	*eTopY = this->eTopY;
	*eWidth = this->eWidth;
	*eHeight = this->eHeight;
}

void productButton::setAllDimensions(float rLeftX, float rTopY, float rWidth, float rHeight, float eLeftX, float eTopY, float eWidth, float eHeight)
{
	this->rLeftX = rLeftX;
	this->rTopY = rTopY;
	this->rWidth = rWidth;
	this->rHeight = rHeight;
	this->eLeftX = eLeftX;
	this->eTopY = eTopY;
	this->eHeight = eHeight;
	this->eWidth = eWidth;

	
	margin = BUTTON_MARGIN(this->rWidth, this->rHeight);
	calculateCurrentDimensions();
	setExpandedBmp();
	setReducedBmp();
}

void productButton::getAllDimensions(float * rLeftX, float * rTopY, float * rWidth, float * rHeight, float * eLeftX, float * eTopY, float * eWidth, float * eHeight)
{
	getReducedDimensions(rLeftX, rTopY, rWidth, rHeight);
	getExpandedDimensions(eLeftX, eTopY, eWidth, eHeight);
}

void productButton::setProductCost()
{
//	cost = Unit::getCost(unitSpecificType);
}

void productButton::calculateCurrentDimensions()
{
	if (selected)
	{
		//Ocupa todo el espacio disponible
		width = eWidth;
		height = eHeight;
		leftX = eLeftX;
		topY = eTopY;
	}
	else
	{
		//Las dimensiones corresponden a un cuadrado centrado 
		width = height = min(rWidth, rHeight);
		leftX = rLeftX + rWidth / 2.0 - width / 2.0;
		topY = rTopY + rHeight / 2.0 - height / 2.0;
	}
}





//void productButton::setResizedBmp()
//{
//	if (resizedBmp != nullptr)
//	{
//		al_destroy_bitmap(resizedBmp);
//	}
//	resizedBmp = al_create_bitmap(width, height);
//
//	//hacer backup del taregt bitmap actual y dibujar el boton en resizedBmp
//	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
//	al_set_target_bitmap(resizedBmp);
//
//	if (selected)
//	{
//		al_draw_filled_rounded_rectangle(margin, margin,
//			eWidth - margin, eHeight - margin,
//			BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
//			al_color_name(WHEEL_COLOR));	//Sacar el define de WHEEL COLOR y hacerlo para todos los basic types
//		al_draw_scaled_bitmap(unformattedBmp, 0, 0,
//			al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
//			margin * 2, margin * 2,
//			height / 4.0, width / 4.0,
//			0);
//		al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0, 0, "FIREPOWER");
//		al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 3 * smallFontHeight, 0, "REDUCED FIREPOWER");
//		al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 6 * smallFontHeight, 0, "TERRAIN MOVEMENT COST");
//	}
//	else
//	{
//		//Dibujar fondo
//		al_draw_filled_rounded_rectangle(margin, margin,
//			width - margin, height - margin,
//			BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
//			al_color_name(WHEEL_COLOR));	//Sacar el define de WHEEL COLOR y hacerlo para todos los basic types
//
//		//Dibujar la unidad
//		al_draw_scaled_bitmap(unformattedBmp,
//			0, 0,
//			al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
//			margin * 2, margin * 2,
//			width - margin * 2 * 2, height - margin * 2 * 2,
//			0);	//TODO: sacar magic numbers
//
//		//Dibujar borde
//		al_draw_rounded_rectangle(margin, margin,
//			width - margin, height - margin,
//			BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
//			{ 0.7f, 0.7f, 0.7f, 1 }, 6);	//TODO: sacar magic numbers
//
//											//al_draw_rounded_rectangle(margin, margin,
//											//	buttonSide - margin, buttonSide - margin, 
//											//	BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
//											//	{ 1, 1, 1, 1 }, 2);	//TODO: sacar magic numbers
//
//		ALLEGRO_BITMAP * auxBmp = nullptr;
//
//		//Dibujar el precio
//		auxBmp = al_load_bitmap(IMAGE_PATH "coin.png");
//		if (auxBmp == nullptr)
//		{
//			cout << "No se pudo cargar la imagen de moneda" << endl;
//			valid = false;
//			return;
//		}
//
//		//Dibujar moenda
//		al_draw_scaled_bitmap(auxBmp,
//			0, 0,
//			al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
//			0, width - COIN_HEIGHT_IN_MARGINS * margin,
//			COIN_HEIGHT_IN_MARGINS * margin, COIN_HEIGHT_IN_MARGINS * margin,
//			0);
//
//		//Dibujar el precio
//		al_draw_textf(smallFont, al_color_name("white"), COIN_HEIGHT_IN_MARGINS * margin,
//			height - COIN_HEIGHT_IN_MARGINS * margin / 2.0 - al_get_font_line_height(smallFont) / 2.0,	//centrar verticalmente
//			0, "%d", cost);
//		al_destroy_bitmap(auxBmp);
//
//		//switch (unitBasicType = u->getBasicType())
//		switch (unitBasicType = TREAD)
//		{
//		case WHEEL:
//			break;
//		case TREAD:
//			auxBmp = al_load_bitmap(TREAD_LOGO_BMP);	//cargar el "logo" del basic type de la unidad
//			if (auxBmp == nullptr)
//			{
//				cout << "No se cargo el logo de tread" << endl;
//				valid = false;
//				return;
//			}
//			break;
//		case FOOT:
//			break;
//		default:	//TODO: ???
//			break;
//		}
//
//		//una vez cargado sin error, dibujar el logo del basic type con el tamanio adecuado y luego eliminar
//		al_draw_scaled_bitmap(auxBmp,
//			0, 0,	//TODO: dibujarle el tipo
//			al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
//			width - margin * 4, height * 2.0 / 3.0,
//			width * 2.0 / 5.0, height * 2.0 / 5.0, 0);		//TODO: sacar magic numbers
//		al_destroy_bitmap(auxBmp);
//	}
//	//TODO: agregar donde se escribe el basic type
//
//	al_set_target_bitmap(backupBmp);
//
//}   //TODO: controlr de parametros (que no haya nada es nullptr)
