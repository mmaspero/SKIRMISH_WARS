#include "productButton.h"

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "drawingFunctions.h"
#include "paths.h"


#define	CONFIG_FILE "productButton.cfg"

#define WHEEL_BG_COLOR	"thistle"
#define TREAD_BG_COLOR  "thistle"
#define FOOT_BG_COLOR   "thistle"

#define FONT_NAME "media/font/Minecraft.ttf"
#define	BIG_FONT_SIZE    30

#define BUTTON_MARGIN(w, h) (((w)>(h) ? h : w) / 20.0)
#define BUTTON_CORNER_ROUNDNESS 10

#define COIN_HEIGHT_IN_MARGINS 6	//La moneda que indica plata tiene COIN_HEIGHT_IN_MARGIN veces la altura del margen
#define LOGO_SIDE_IN_MARGINS 7

#define ANTIAIR_SPRITE "media/img/sprites/antiair_red.png"
#define ANTIAIR_NAME "ANTIAIR"

#define TREAD_LOGO_BMP "media/img/tread_logo.png"
#define FOOT_LOGO_BMP TREAD_LOGO_BMP
#define WHEEL_LOGO_BMP TREAD_LOGO_BMP

using namespace std;

//productButton::productButton(Unit * u, float rLeftX, float rTopY, float rWidth, float rHeight, 
productButton::productButton(float rLeftX, float rTopY, float rWidth, float rHeight,
	float eLeftX, float eTopY, float eWidth, float eHeight)
	: button(rLeftX, rTopY, rWidth, rHeight)
{
	if (valid)	//Proseguir solo si construyo button sin problemas
	{
		resizedBmp = nullptr;	//NO SE USA!!! EN CAMBIO SE USA reducedBmp y expandedBmp

		//TODO: validacion de parametros
		this->rLeftX = rLeftX;
		this->rTopY = rTopY;
		this->rWidth = rWidth;
		this->rHeight = rHeight;

		this->eLeftX = eLeftX;
		this->eTopY = eTopY;
		this->eWidth = eWidth;
		this->eHeight = eHeight;
		
		//switch (unitSpecificType = u->getType())
		switch (unitSpecificType = ANTIAIR)
		{
		case RECON:
			break;
		case ROCKET:
			break;
		case MECH:
			break;
		case INFANTRY:
			break;
		case TANK:
			break;
		case ARTILLERY:
			break;
		case ANTIAIR:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case APC:
			break;
		case MEDTANK:
			break;
		default:
			break;
		}
		if (unformattedBmp == nullptr)
		{
			cout << "No se pudo cargar el sprite " << ANTIAIR_SPRITE << endl;
			valid = false;
			return;
		}

		margin = BUTTON_MARGIN(rWidth, rHeight);	//definir el margen con las dimensiones del boton reducido

		calculateCurrentDimensions();
		setExpandedBmp();
		setReducedBmp();


		//TODO: copiar toda la info necesaria y borrar lo de abajo
		cost = 37;
		for (int i = 0; i < N_B_TYPES; i++)	//Cuantos HP le saca a cada tipo basico de unidad
		{
			firepower[i] = i * 2;
			firepowerReduced[i] = i;
		}
		for (int i = 0; i < N_TERRAINS; i++)
		{
			movingPoints[i] = i;
		}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

productButton::productButton(float rLeftX, float rTopY, float rWidth, float rHeight,
	float eLeftX, float eTopY, float eWidth, float eHeight, unit_t unitSpecificType)
	: button(rLeftX, rTopY, rWidth, rHeight)
{
	if (valid)	//Proseguir solo si construyo button sin problemas
	{
		resizedBmp = nullptr;	//NO SE USA!!! EN CAMBIO SE USA reducedBmp y expandedBmp

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
		//switch (unitSpecificType = u->getType())
		switch (unitSpecificType)
		{
		case RECON:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case ROCKET:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case MECH:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case INFANTRY:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case TANK:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case ARTILLERY:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case ANTIAIR:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case APC:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		case MEDTANK:
			unformattedBmp = al_load_bitmap(ANTIAIR_SPRITE);
			break;
		default:
			break;
		}
		if (unformattedBmp == nullptr)
		{
			cout << "No se pudo cargar el sprite " << ANTIAIR_SPRITE << endl;
			valid = false;
			return;
		}

		margin = BUTTON_MARGIN(rWidth, rHeight);	//definir el margen con las dimensiones del boton reducido

		calculateCurrentDimensions();
		setExpandedBmp();
		setReducedBmp();


		//TODO: copiar toda la info necesaria y borrar lo de abajo
		cost = 37;
		for (int i = 0; i < N_B_TYPES; i++)	//Cuantos HP le saca a cada tipo basico de unidad
		{
			firepower[i] = i * 2;
			firepowerReduced[i] = i;
		}
		for (int i = 0; i < N_TERRAINS; i++)
		{
			movingPoints[i] = i;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

productButton::~productButton()
{
	//TODO: todo
}

bool productButton::getCanBuy()
{
	return canBuy;
}

void productButton::setCanBuy(bool canBuy)
{
	this->canBuy = canBuy;
}

unit_t productButton::getUnitSpecificType()
{
	return unitSpecificType;
}

void productButton::setUnitSpecificType(unit_t unitSpecificType)
{
	this->unitSpecificType = unitSpecificType;
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
			al_flip_display();
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
//		auxBmp = al_load_bitmap("media/img/coin.png");
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

bool productButton::setReducedBmp()
{
	string configFile(CONFIG_PATH); 
	configFile += "/";
	configFile += CONFIG_FILE;

//DEBUG	cout << configFile << endl;

	ALLEGRO_CONFIG * cfg = al_load_config_file(configFile.c_str());

	if (reducedBmp != nullptr)
	{
		al_destroy_bitmap(reducedBmp);
	}
	reducedBmp = al_create_bitmap(width, height);

	//hacer backup del target bitmap actual y dibujar el boton en resizedBmp
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
	al_set_target_bitmap(reducedBmp);

	//Cargar el "logo"  y el color de fondo correspondiente al basic type de la unidad

	ALLEGRO_BITMAP * auxBmp = nullptr;
	ALLEGRO_COLOR bgColor;

	//switch (unitBasicType = u->getBasicType())
	switch (unitBasicType = TREAD)
	{
	case WHEEL:
		bgColor = al_color_name(WHEEL_BG_COLOR);
		auxBmp = al_load_bitmap(WHEEL_LOGO_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se cargo el logo de wheel" << endl;
			if (reducedBmp != nullptr)
			{
				al_destroy_bitmap(reducedBmp);
			}
			al_set_target_bitmap(backupBmp);
			return false;
		}
		break;
	case TREAD:
		bgColor = al_color_name(TREAD_BG_COLOR);
		auxBmp = al_load_bitmap(TREAD_LOGO_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se cargo el logo de tread" << endl;
			if (reducedBmp != nullptr)
			{
				al_destroy_bitmap(reducedBmp);
			}
			al_set_target_bitmap(backupBmp);
			return false;
		}
		break;
	case FOOT:
		bgColor = al_color_name(WHEEL_BG_COLOR);
		auxBmp = al_load_bitmap(FOOT_LOGO_BMP);
		if (auxBmp == nullptr)
		{
			cout << "No se cargo el logo de foot" << endl;
			if (reducedBmp != nullptr)
			{
				al_destroy_bitmap(reducedBmp);
			}
			al_set_target_bitmap(backupBmp);
			return false;
		}
		break;
	default:	//TODO: ???
		break;
	}
	//Dibujar fondo
	al_draw_filled_rounded_rectangle(margin, margin,
		width - margin, height - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		bgColor);

	//TODO: y si unformattedBmp = nullptr?

	//Dibujar la unidad
	al_draw_tinted_scaled_bitmap(unformattedBmp, { 0, 1, 1, 1 },
		0, 0,
		al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
		margin * 2, margin * 2,
		width - margin * 2 * 2, height - margin * 2 * 2,
		0);	//TODO: sacar magic numbers

	//Dibujar borde
	al_draw_rounded_rectangle(margin, margin,
		width - margin, height - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		{ 0.7f, 0.7f, 0.7f, 1 }, 6);	//TODO: sacar magic numbers

	//Dibujar el logo del basic type con el tamanio adecuado y luego eliminar
	al_draw_scaled_bitmap(auxBmp,
		0, 0,
		al_get_bitmap_width(auxBmp),				al_get_bitmap_height(auxBmp),
		width - margin * LOGO_SIDE_IN_MARGINS,	height - margin * LOGO_SIDE_IN_MARGINS,
		margin * LOGO_SIDE_IN_MARGINS,			margin * LOGO_SIDE_IN_MARGINS, 0);		//TODO: sacar magic numbers

	//Cargar imagen de la moneda
	auxBmp = al_load_bitmap("media/img/coin.png");	//TODO: sacar de define
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
		0, 0,
		al_get_bitmap_width(auxBmp), al_get_bitmap_height(auxBmp),
		0, width - COIN_HEIGHT_IN_MARGINS * margin,
		COIN_HEIGHT_IN_MARGINS * margin, COIN_HEIGHT_IN_MARGINS * margin,
		0);

	ALLEGRO_FONT * font = al_load_font(FONT_NAME, - margin * COIN_HEIGHT_IN_MARGINS / 2.0, 0);
	if (font == nullptr)
	{
		cout << "No se pudo cargar la font para el reduced Bmp";
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
	expandedBmp = al_create_bitmap(eWidth, eHeight);

	//hacer backup del taregt bitmap actual y dibujar el boton en resizedBmp
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();
	al_set_target_bitmap(expandedBmp);

	al_draw_filled_rounded_rectangle(margin, margin,
		eWidth - margin, eHeight - margin,
		BUTTON_CORNER_ROUNDNESS, BUTTON_CORNER_ROUNDNESS,
		al_color_name(WHEEL_BG_COLOR));	//Sacar el define de WHEEL COLOR y hacerlo para todos los basic types
	al_draw_scaled_bitmap(unformattedBmp, 0, 0,
		al_get_bitmap_width(unformattedBmp), al_get_bitmap_height(unformattedBmp),
		margin * 2, margin * 2,
		eHeight / 4.0 - margin * 2, eWidth / 4.0 - margin * 2,
		0);
	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0, 0, "FIREPOWER");
	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 3 * smallFontHeight, 0, "REDUCED FIREPOWER");
	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 6 * smallFontHeight, 0, "TERRAIN MOVEMENT COST");


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


