#include "scoreBoard.h"

#include <iostream>
#include "paths.h"
#include "../Game model/types.h"

#define MAX_HP_ROUND_AVATAR 1000	//TODO: mover de aca
#define MAX_HQ_HP 25

#define HQ_HP_FONT_NAME FONT_PATH "ttf.ttf"
#define FONT_SIZE 45
#define HP_BAR_TITLE "HQ HP"
#define HP_BAR_MARGIN 20
#define HP_BAR_HEIGHT_RATIO 0.5 //MULTIPLICADO POR contentHeight DA LA ALTURA DE LAS HPbar
#define USER_COLOR 1,0,0,1
#define OPPONENT_COLOR 0,0,1,1

using namespace std;

scoreBoard::scoreBoard(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height, 
	ALLEGRO_BITMAP * myAvatarBmp, ALLEGRO_BITMAP * theirAvatarBmp, unsigned int maxHP, 
	unsigned int myMoney, unsigned int myUnits, unsigned int myCities)
	: contentBox(display, startX, startY, width, height, true)
{
	if (valid)
	{
		displaySectionType = SCOREBOARD;

		this->myMoney = myMoney;	//TODO: validacion de parametros
		this->myUnits = myUnits;
		this->myCities = myCities;

		if (myAvatarBmp == nullptr)
		{
			valid = false;
			cout << "No se pudo cargar el avatar del usuario" << endl;
			return;
		}
		else if (theirAvatarBmp == nullptr)
		{
			valid = false;
			cout << "No se pudo cargar el avatar del oponente" << endl;
			return;
		}
		this->myAvatarBmp = myAvatarBmp;
		this->theirAvatarBmp = theirAvatarBmp;

		//////creacion de los avatares formateados//////
		int radius = contentHeight / 2;					//El diametro es toda la altura disponible del contentBox
		
		myAvatar_f = new avatarRoundHP(myAvatarBmp, radius, MAX_HP_ROUND_AVATAR,
								contentStartX + radius, contentStartY + radius);
		theirAvatar_f = new avatarRoundHP(theirAvatarBmp, radius, MAX_HP_ROUND_AVATAR,
								contentStartX + contentWidth - radius, contentStartY + radius);
		if (!myAvatar_f->isValid())
		{
			cout << "Error en la creacion del avatar formateado del usuario" << endl;
			valid = false;
			return;
		}
		else if (!theirAvatar_f->isValid())
		{
			cout << "Error en la creacion del avatar formateado del oponente" << endl;
			valid = false;
			return;
		}

		myAvatar_f->setScoreColor(al_map_rgba_f(USER_COLOR));
		theirAvatar_f->setScoreColor(al_map_rgba(OPPONENT_COLOR));

		//////creacion de la frase entre HP bars//////
		font = al_load_ttf_font(HQ_HP_FONT_NAME, FONT_SIZE, 0);
		if (font == nullptr)
		{
			cout << "No se pudo cargar la font para el HQ HP" << endl;	
			HPbarTitleLength = 0;
			//No poner valid = false p/q font no es esencial para el correcto funcionamiento de scoreBoard
		}
		else
		{
			HPbarTitleLength = al_get_text_width(font, HP_BAR_TITLE);
		}


		//////creacion de ambas HP bars//////
		HPbarMargin = HP_BAR_MARGIN;

		float HPbarWidth = contentWidth / 2 - HPbarTitleLength / 2 - HPbarMargin * 2 - 2 * radius;
		float HPbarHeight = contentHeight * HP_BAR_HEIGHT_RATIO;

		hpBarPalette_t hpPal;
		{
			hpPal.frameBase = { 0, 0, 0, 1 };
			hpPal.frameHighlight = { 1, 1, 1, 1 };
			hpPal.background = { 0.5, 0, 0, 1 };	//TODO: sacar los magic numbers
			hpPal.hp = { 1,0,0,1 };
		}
		myHQHPbar = new HPbar(contentStartX + 2 * radius + HPbarMargin, 
							contentStartY + (contentHeight - HPbarHeight) / 2,
							HPbarWidth, HPbarHeight, CP_HQ, hpPal, false);
		{
			hpPal.background = { 0, 0, 0.5, 1 };
			hpPal.hp = { 0, 0, 1, 1 };
		}
		theirHQHPbar = new HPbar(contentStartX + contentWidth / 2 + HPbarTitleLength / 2 + HPbarMargin, 
							contentStartY + (contentHeight - HPbarHeight) / 2, 
							HPbarWidth, HPbarHeight, CP_HQ, hpPal, true);

		if (!myHQHPbar->isValid())
		{
			cout << "No se pudo construir la HP bar del usuario" << endl;
			valid = false;
			return;
		}
		else if (!theirHQHPbar->isValid())
		{
			cout << "No se pudo construir la HP bar del oponente" << endl;
			valid = false;
			return;
		}
	}
}

scoreBoard::~scoreBoard()
{
	if (font != nullptr)
	{
		al_destroy_font(font);
	}
	delete myAvatar_f;
	delete theirAvatar_f;
	delete myHQHPbar;
	delete theirHQHPbar;
}

HPbar * scoreBoard::getMyHQHPbar()
{
	return myHQHPbar;
}

HPbar * scoreBoard::getTheirHQHPbar()
{
	return theirHQHPbar;
}

void scoreBoard::setMyMoney(unsigned int myMoney)
{
	this->myMoney = myMoney;
}

void scoreBoard::setMyUnits(unsigned int myUnits)
{
	this->myUnits = myUnits;
}

void scoreBoard::setMyCities(unsigned int myCities)
{
	this->myCities = myCities;
}

void scoreBoard::drawContent()
{
	myAvatar_f->draw();
	theirAvatar_f->draw();

	myHQHPbar->draw();
	theirHQHPbar->draw();

	al_draw_text(font, al_map_rgb_f(0, 0, 0), contentStartX + contentWidth / 2 - HPbarTitleLength / 2,
		contentStartY + contentHeight / 3.0, 0, HP_BAR_TITLE);
}

void scoreBoard::resizeContent()
{
	int radius = contentHeight / 2;
	theirAvatar_f->setRadius(radius);
	theirAvatar_f->setPosition(contentStartX + contentWidth - radius, contentStartY + radius);
	myAvatar_f->setRadius(radius);
	myAvatar_f->setPosition(contentStartX + radius, contentStartY + radius);

	float HPbarWidth = contentWidth / 2 - HPbarTitleLength / 2 - HPbarMargin * 2 - 2 * radius;
	float HPbarHeight = contentHeight * HP_BAR_HEIGHT_RATIO;

	theirHQHPbar->setWidth(HPbarWidth);
	theirHQHPbar->setHeight(HPbarHeight);
	theirHQHPbar->setPosition(contentStartX + contentWidth / 2 + HPbarTitleLength / 2 + HPbarMargin,
						contentStartY + (contentHeight - HPbarHeight) / 2);
	myHQHPbar->setWidth(HPbarWidth);
	myHQHPbar->setHeight(HPbarHeight);
	myHQHPbar->setPosition(contentStartX + 2 * radius + HPbarMargin,
						contentStartY + (contentHeight - HPbarHeight) / 2);
}
