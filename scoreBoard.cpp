#include "scoreBoard.h"

#define MAX_HP 1000	//TODO: mover de aca
#define MAX_HQ_HP 25

#define HQ_HP_FONT_NAME "media/font/ttf.ttf"
#define FONT_SIZE 45
#define HP_BAR_TITLE "HQ HP"
#define HP_BAR_MARGIN 20
#define HP_BAR_HEIGHT_RATIO 0.5 //MULTIPLICADO POR contentHeight DA LA ALTURA DE LAS HPbar

scoreBoard::scoreBoard(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height, 
	ALLEGRO_BITMAP * myAvatarBmp, ALLEGRO_BITMAP * theirAvatarBmp, unsigned int maxHP)
	:contentBox(display, startX, startY, width, height, true)
{
	if (valid)
	{
		if (myAvatarBmp != nullptr)
		{
			this->myAvatarBmp = myAvatarBmp;	//TODO: avisar si hay error
		}
		if (theirAvatarBmp != nullptr)
		{
			this->theirAvatarBmp = theirAvatarBmp;
		}

		int radius = contentHeight / 2;					//El diametro es toda la altura disponible del contentBox
		myAvatar_f = new avatarRoundHP(myAvatarBmp, radius, MAX_HP, 
								contentStartX + radius, contentStartY + radius);	
		myAvatar_f->setScoreColor({ 1,0,0,1 });			//TODO: sacar magic numbers
		theirAvatar_f = new avatarRoundHP(theirAvatarBmp, radius, MAX_HP, 
								contentStartX + contentWidth - radius, contentStartY + radius);
		theirAvatar_f->setScoreColor({ 0,0,1,1 });		//TODO: sacar magic numbers

		font = al_load_ttf_font(HQ_HP_FONT_NAME, FONT_SIZE, 0);
		HPbarTitleLength = (font == nullptr) ? 0 : al_get_text_width(font, HP_BAR_TITLE);

		HPbarMargin = HP_BAR_MARGIN;

		float HPbarWidth = contentWidth / 2 - HPbarTitleLength / 2 - HPbarMargin * 2 - 2 * radius;
		float HPbarHeight = contentHeight * HP_BAR_HEIGHT_RATIO;

		hpBarPalette_t hpPal;
		hpPal.frameBase = { 0, 0, 0, 1 };
		hpPal.frameHighlight = { 1, 1, 1, 1 };
		hpPal.background = { 0.5, 0, 0, 1 };	//TODO: sacar los magic numbers
		hpPal.hp = { 1,0,0,1 };

		myHQHP = new HPbar(contentStartX + 2 * radius + HPbarMargin, 
							contentStartY + (contentHeight - HPbarHeight) / 2,
							HPbarWidth, HPbarHeight, MAX_HQ_HP, hpPal, false);
		myHQHP->setCurrentHP(myHQHP->getCurrentHP() / 2);

		hpPal.background = { 0, 0, 0.5, 1 };
		hpPal.hp = { 0, 0, 1, 1 };

		theirHQHP = new HPbar(contentStartX + contentWidth / 2 + HPbarTitleLength / 2 + HPbarMargin, 
							contentStartY + (contentHeight - HPbarHeight) / 2, 
							HPbarWidth, 
							HPbarHeight, 
							MAX_HQ_HP, 
							hpPal,
							true);
		theirHQHP->setCurrentHP(theirHQHP->getCurrentHP() * 9 / 10);

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
	delete myHQHP;
	delete theirHQHP;
}

void scoreBoard::drawContent()
{
	myAvatar_f->draw();
	theirAvatar_f->draw();

	myHQHP->draw();
	theirHQHP->draw();

	al_draw_text(font, al_map_rgb_f(0, 0, 0), contentStartX + contentWidth / 2 - HPbarTitleLength / 2,
		contentStartY + contentHeight / 3.0, 0, "HQ HP");
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

	theirHQHP->setWidth(HPbarWidth);
	theirHQHP->setHeight(HPbarHeight);
	theirHQHP->setPosition(contentStartX + contentWidth / 2 + HPbarTitleLength / 2 + HPbarMargin,
						contentStartY + (contentHeight - HPbarHeight) / 2);
	myHQHP->setWidth(HPbarWidth);
	myHQHP->setHeight(HPbarHeight);
	myHQHP->setPosition(contentStartX + 2 * radius + HPbarMargin, 
						contentStartY + (contentHeight - HPbarHeight) / 2);
}
