#include "toolbox.h"

#include <iostream>

#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include "simpleButton.h"
#include "productButton.h"
#include "config\sprite_config.h"
#include "HPbar.h"
#include "paths.h"	

#define BUTTONS_PER_ROW 3
#define PRODUCT_SECTION_RELATIVE_H 0.9
#define BUTTON_MARGIN(w, h) (((w)>(h) ? h : w) / 20.0)
#define BUTTON_CORNER_ROUNDNESS 10

#define FONT_NAME FONT_PATH "Minecraft.ttf"
#define	BIG_FONT_SIZE    30
#define SMALL_FONT_SIZE_IN_HEIGHT (1/15.0)	


using namespace std;

toolbox::toolbox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height)
	: contentBox(display, startX, startY, width, height, false)
{
	if (valid)
	{
		displaySectionType = TOOLBOX;

		status = EMPTY_MY_TURN;	//TODO: que no empiece siempre en  mi turno.

		bool buttonValid = true;
		productButton * b = nullptr;

		//creo los product button con tamanios arbitrarios.
		for (int i = 0; i < N_UNIT_TYPES; i++)
		{
			b = new productButton(//Unit * u
				1,1,1,1,1,1,1,1, (unit_t)i);
			b->hiddenOn();
			b->selectedOff();
			buttonList.push_back(b);
			if (!buttonList.back()->isValid())
			{
				buttonValid = false;
			}
		}
		//Seteo el tamanio de los productButtons y creo los simpleButtons
		resizeContent();

		//Si hubo un error en el constructor de algun boton, eliminar toda la lista
		if (!buttonValid)	
		{
			buttonList.clear();
		}
		valid = buttonValid;
	}
}

toolbox::~toolbox()
{
	buttonList.clear();
}

void toolbox::selectProduct(unit_t unitSpecificType)
{
	for (std::list<button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			if (((productButton *)(*it))->getUnitSpecificType() == unitSpecificType)
			{
				((productButton *)(*it))->selectedOn();
				((productButton *)(*it))->hiddenOff();
			}
			else
			{
				((productButton *)(*it))->selectedOff();
				((productButton *)(*it))->hiddenOn();
			}
		}
	}
	status = SHOWING_ONE_PRODUCT;
}

unit_t toolbox::getSelectedProduct()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON && ((productButton *)(*it))->isSelected())
		{
			return ((productButton *)(*it))->getUnitSpecificType();
		}
	}
	return N_UNIT_TYPES;
}

toolboxStatus_t toolbox::getStatus()
{
	return status;
}

button * toolbox::getButton(unsigned int xPixel, unsigned int yPixel)
{
	button * buttonSelected = nullptr;
	

	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isItHere(xPixel, yPixel))
		{
			switch (status)
			{
			case EMPTY_MY_TURN: case SHOWING_UNIT_INFO:
				if ((*it)->getType() == SIMPLE_BUTTON && 
					(((simpleButton *)(*it))->getSimpleType() == STORE_BUTTON || ((simpleButton *)(*it))->getSimpleType() == PASS_BUTTON))
				{
					buttonSelected = (*it);
				}
				break;
			case SHOWING_ONE_PRODUCT:
				if ((*it)->getType() == SIMPLE_BUTTON &&
					(((simpleButton *)(*it))->getSimpleType() == BACK_BUTTON || ((simpleButton *)(*it))->getSimpleType() == BUY_BUTTON))
				{
					buttonSelected = (*it);
				}
				break;
			case SHOWING_ALL_PRODUCTS:
				if ( (*it)->getType() == PRODUCT_BUTTON ||
					((*it)->getType() == SIMPLE_BUTTON && ((simpleButton *)(*it))->getSimpleType() == PASS_BUTTON ))
				{
					buttonSelected = (*it);
				}
				break;
			default:
				break;
			}

		}
	}
	return buttonSelected;
}

void toolbox::goToShowingUnitInfo(Unit * u)
{
	status = SHOWING_UNIT_INFO;

	this->u = u;
}

void toolbox::goToStore()
{
	if (status == EMPTY_MY_TURN || status == SHOWING_ONE_PRODUCT || status == SHOWING_UNIT_INFO)
	{
		status = SHOWING_ALL_PRODUCTS;
		for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
		{
			if ((*it)->getType() == PRODUCT_BUTTON)
			{
				((productButton *)(*it))->hiddenOff();
				((productButton *)(*it))->selectedOff();
			}
		}
	}
}

void toolbox::goToMyTurn()
{
	status = EMPTY_MY_TURN;
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->hiddenOn();
			((productButton *)(*it))->selectedOff();
		}
	}
}

void toolbox::goToTheirTurn()
{
	status = EMPTY_THEIR_TURN;
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			((productButton *)(*it))->hiddenOff();
			((productButton *)(*it))->selectedOff();
		}
	}
}

void toolbox::setProductCosts()
{
	acknowledgeResize();	//Para que se creen los bmps con el precio.
}

bool toolbox::createSimpleButtons()
{
	std::cout << "creo simple buttons" << std::endl;
	bool buttonValid = true;		//indica si hubo un error en la creacion de alguno de los botones.

	//dimensiones y coordenadas de los botones. 
	//Lo unico que cambia en los diferentes simpleButtons la coordenada x
	//(la coordenada y, el ancho, y el alto se mantienen)

	float buttonHeight = contentHeight * (1 - PRODUCT_SECTION_RELATIVE_H);
	float buttonWidth = contentWidth / 2.0;
	float buttonTopY = contentStartY + contentHeight * PRODUCT_SECTION_RELATIVE_H;

	simpleButton * simpleBuy = new simpleButton(BUY_BUTTON, 
		contentStartX,
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleBuy);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simpleStore = new simpleButton(STORE_BUTTON, 
		contentStartX, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleStore);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simpleBack = new simpleButton(BACK_BUTTON, 
		contentStartX + contentWidth / 2.0, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simpleBack);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	simpleButton * simplePass = new simpleButton(PASS_BUTTON, 
		contentStartX + contentWidth / 2.0, 
		buttonTopY,
		buttonWidth, 
		buttonHeight);
	buttonList.push_back(simplePass);
	if (!buttonList.back()->isValid())
	{
		buttonValid = false;
	}

	return buttonValid;
}

void toolbox::drawContent()
{
	switch (status)
	{
	case EMPTY_MY_TURN:
		drawEmptyMyTurn();
		break;
	case SHOWING_ALL_PRODUCTS:
		drawShowingAllProducts();
		break;
	case SHOWING_ONE_PRODUCT:
		drawShowingOneProduct();
		break;
	case SHOWING_UNIT_INFO:
		drawShowingUnitInfo();
		break;
	}
}

void toolbox::resizeContent()
{
	float productButtonSectionHeight = PRODUCT_SECTION_RELATIVE_H * contentHeight;
	std::list<button*>::iterator it = buttonList.begin();
	//for (std::list<button*>::iterator it = buttonList.begin(); 
	//	it != buttonList.end(); 
	//	it++)
	do
	{

		if ((*it)->getType() == PRODUCT_BUTTON)
		{
			unit_t unitSpecificType = ((productButton*)(*it))->getUnitSpecificType();

			int aux = (unitSpecificType % BUTTONS_PER_ROW);

			float rWidth  = contentWidth / (float)BUTTONS_PER_ROW;
			float rHeight = productButtonSectionHeight / (N_UNIT_TYPES / (int)BUTTONS_PER_ROW);
			float rLeftX  = contentStartX + rWidth * aux;
			float rTopY   = contentStartY + rHeight * (unitSpecificType / (int)BUTTONS_PER_ROW);

			((productButton *)(*it))->setAllDimensions(
				rLeftX, rTopY, rWidth, rHeight,
				contentStartX, contentStartY, contentWidth, contentHeight);
			it++;
		}
		else if ((*it)->getType() == SIMPLE_BUTTON)
		{
			it = buttonList.erase(it);		//el iterador se incrementa en erase()
			std::cout << "destruyo simple buttons " << std::endl;
		}
	}
	while ( it != buttonList.end());
	//como buttonList.erase(it) incrementa el iterador, no lo incremento en el statement de salida del while 

	std::cout << "Cantidad de botones: " << buttonList.size() << " - ";
	createSimpleButtons();
	std::cout << buttonList.size() << std::endl; 
}

void toolbox::drawEmptyMyTurn()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid())
		{
			button * b = (*it);
			if (b->getType() == SIMPLE_BUTTON &&
				(((simpleButton*)b)->isItStore() || ((simpleButton*)b)->isItPass()))
			{
				b->draw();
			}
		}
	}
}

void toolbox::drawEmptyTheirTurn()
{
}

void toolbox::drawShowingAllProducts()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid())
		{
			button * b = (*it);
			if (b->getType() == PRODUCT_BUTTON)
			{
				b->draw();
			}
			else if (b->getType() == SIMPLE_BUTTON && ((simpleButton*)b)->isItPass())
			{
				b->draw();
			}
		}
	}
}

void toolbox::drawShowingOneProduct()
{
	for (std::list<button *>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it)->isValid())
		{
			button * b = (*it);
			if (b->getType() == PRODUCT_BUTTON)
			{
				if (b->isSelected())
				{
					b->draw();
				}
			}
			else if (b->getType() == SIMPLE_BUTTON &&
				(((simpleButton*)b)->isItBack() || ((simpleButton*)b)->isItBuy()))
			{
				b->draw();
			}
		}	//TODO: hacer mas compacto pero no croto
	}
}

void toolbox::drawShowingUnitInfo()
{
	if (u == nullptr || u->getType() == N_UNIT_TYPES) { return; }

	//Creo boton auxiliar para usar el expandedBmp para mostrar la unit info.
	productButton auxButton(10, 10, 10, 10, 10, 10,	
		contentWidth, contentHeight * PRODUCT_SECTION_RELATIVE_H, u->getType());

	if (!auxButton.isValid()) { return; }
	
	ALLEGRO_BITMAP * unitInfoBmp = auxButton.getExpandedBmp();
	//Hago backup del target bitmap actual para dibujar momentaneamente en el unitInfoBmp y no en la pantalla
	ALLEGRO_BITMAP * backupBmp = al_get_target_bitmap();	
	al_set_target_bitmap(unitInfoBmp);

	//agrego HP:
	unsigned int w = al_get_bitmap_width(unitInfoBmp), h = al_get_bitmap_height(unitInfoBmp);
	float smallFontHeight = h * SMALL_FONT_SIZE_IN_HEIGHT;
	ALLEGRO_FONT * smallFont = al_load_font(FONT_NAME, -smallFontHeight, 0);
	if(smallFont != nullptr)
	{
		al_draw_textf(smallFont, { 1,1,1,1 }, w / 2.0, h / 5, 0, "%d/%d", u->getHP(), u->getDefense(u->getType()));
	}

	al_set_target_bitmap(backupBmp);
	drawEmptyMyTurn();
	al_draw_bitmap(unitInfoBmp, contentStartX, contentStartY, 0);
	al_destroy_bitmap(unitInfoBmp);
	
	

	//unit_t unitSpecificType = u->getType();
	//basicUnitType_t unitBasicType = u->getBasicType();
	//unsigned int firepower[N_BASIC_U_TYPES];	//Cuantos HP le saca a cada tipo basico de unidad
	//unsigned int firepowerReduced[N_BASIC_U_TYPES];
	//unsigned int movingPoints[N_TERRAINS];
	//unsigned int range[2];	//Maximo y minimo rango
	//unsigned int healthPoints;
	//ALLEGRO_COLOR bgColor;
	//ALLEGRO_BITMAP * unitSprite;
	//ALLEGRO_BITMAP * basicTypeLogo = nullptr;
	//float width = contentWidth;
	//float height = contentHeight * PRODUCT_SECTION_RELATIVE_H;
	//float margin = BUTTON_MARGIN(width, height);


	//for (int i = 0; i < N_BASIC_U_TYPES; i++)	//Cuantos HP le saca a cada tipo basico de unidad
	//{
	//	firepower[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, false);
	//	firepowerReduced[i] = Unit::getAttackMod(unitSpecificType, (basicUnitType_t)i, false);
	//}
	//for (int i = 0; i < N_TERRAINS; i++)
	//{
	//	movingPoints[i] = Unit::getTerrainMod(unitSpecificType, (terrain_t)i);
	//}
	//Unit::getRange(unitSpecificType, range[0], range[1]);

	////HPbar hpBar();
	//
	////Cargar el sprite de la unidad seleccionada
	//switch (unitSpecificType)
	//{
	//case RECON:
	//	unitSprite = al_load_bitmap(RECON_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << RECON_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case ROCKET:
	//	unitSprite = al_load_bitmap(ROCKET_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << ROCKET_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case MECH:
	//	unitSprite = al_load_bitmap(MECH_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << MECH_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case INFANTRY:
	//	unitSprite = al_load_bitmap(INFANTRY_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << INFANTRY_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case TANK:
	//	unitSprite = al_load_bitmap(TANK_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << TANK_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case ARTILLERY:
	//	unitSprite = al_load_bitmap(ARTILLERY_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << ARTILLERY_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case ANTIAIR:
	//	unitSprite = al_load_bitmap(ANTIAIR_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << ANTIAIR_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case APC:
	//	unitSprite = al_load_bitmap(APC_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << APC_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//case MEDTANK:
	//	unitSprite = al_load_bitmap(MEDTANK_SPRITE_R);
	//	if (unitSprite == nullptr)
	//	{
	//		cout << "No se pudo cargar el sprite " << MEDTANK_SPRITE_R << endl;
	//		valid = false;
	//		return;
	//	}
	//	break;
	//default:
	//	break;
	//}

	////Cargo el color de fondo y el logo del basicType
	//switch (unitBasicType)
	//{
	//case WHEEL:
	//	bgColor = al_color_name(WHEEL_BG_COLOR);
	//	basicTypeLogo = al_load_bitmap(WHEEL_LOGO_BMP);
	//	if (basicTypeLogo == nullptr)
	//	{
	//		std::cout << "No se cargo el logo de wheel" << std::endl;
	//		valid = false;
	//	}
	//	break;
	//case TREAD:
	//	bgColor = al_color_name(TREAD_BG_COLOR);
	//	basicTypeLogo = al_load_bitmap(TREAD_LOGO_BMP);
	//	if (basicTypeLogo == nullptr)
	//	{
	//		std::cout << "No se cargo el logo de tread" << std::endl;
	//		valid = false;
	//	}
	//	break;
	//case FOOT:
	//	bgColor = al_color_name(FOOT_BG_COLOR);
	//	basicTypeLogo = al_load_bitmap(FOOT_LOGO_BMP);
	//	if (basicTypeLogo == nullptr)
	//	{
	//		std::cout << "No se cargo el logo de foot" << std::endl;
	//		valid = false;
	//	}
	//	break;
	//default:	//TODO: ???
	//	break;
	//}

	//al_draw_filled_rounded_rectangle(margin, margin,
	//	width - margin,			height - margin,
	//	BUTTON_CORNER_ROUNDNESS,	BUTTON_CORNER_ROUNDNESS,
	//	bgColor);	//Sacar el define de WHEEL COLOR y hacerlo para todos los basic types
	//al_draw_scaled_bitmap(unitSprite, 0, 0,
	//	al_get_bitmap_width(unitSprite), al_get_bitmap_height(unitSprite),
	//	margin * 2, margin * 2,
	//	height / 3.0 - margin * 2, height / 3.0 - margin * 2,
	//	0);

	//float smallFontHeight = height / 15.0;	//TODO: sacar magic number
	//ALLEGRO_FONT * smallFont = al_load_font(FONT_PATH FONT_NAME, -smallFontHeight, 0);
	//if (smallFont == nullptr)
	//{
	//	std::cout << "No se pudo crear el bitmap expandido del productButton de la unidad de tipo" << \
	//		unitSpecificType << "porque no se pudo cargar la font " << FONT_PATH FONT_NAME << std::endl;
	//}

	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0, 0, "FIREPOWER");	//TODO: sacar magic numbers
	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 2 * smallFontHeight, 0, "REDUCED FIREPOWER");
	//al_draw_text(smallFont, { 1,1,1,1 }, margin * 2, height / 3.0 + 4 * smallFontHeight, 0, "TERRAIN MOV COST");	//TODO: no me entra la palabra completa 

	//float fpSpacing = width / N_BASIC_U_TYPES;	//Distancia entre los valores para firepower
	//float fpX = fpSpacing / 2.0;		//Donde escribo el fp (centrado)
	//for (int i = 0; i < N_BASIC_U_TYPES; i++)
	//{
	//	al_draw_textf(smallFont, { 1,1,1,1 }, fpX, height / 3.0 + smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", firepower[i]);
	//	al_draw_textf(smallFont, { 1,1,1,1 }, fpX, height / 3.0 + 3 * smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", firepowerReduced[i]);
	//	fpX += fpSpacing;
	//}
	//float mpSpacing = width / N_TERRAINS;	//Distancia entre los valores para movingPoints
	//float mpX = mpSpacing / 2.0;		//Donde escribo el mp (centrado)
	//for (int i = 0; i < N_TERRAINS; i++)
	//{
	//	al_draw_textf(smallFont, { 1,1,1,1 }, mpX, height / 3.0 + 5 * smallFontHeight, ALLEGRO_ALIGN_CENTRE, "%d", movingPoints[i]);
	//	mpX += mpSpacing;
	//}

	//if (smallFont != nullptr)
	//{
	//	al_destroy_font(smallFont);
	//}
	//if (unitSprite != nullptr)
	//{
	//	al_destroy_bitmap(unitSprite);
	//}
	//if (basicTypeLogo != nullptr)
	//{
	//	al_destroy_bitmap(basicTypeLogo);
	//}
}

