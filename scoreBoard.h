#pragma once

#include <string>

#include "contentBox.h"
#include "avatarRoundHP.h"
#include "HPbar.h"

class scoreBoard : public contentBox
{
public:
	scoreBoard(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height,
			ALLEGRO_BITMAP * myAvatarBmp, ALLEGRO_BITMAP * theirAvatarBmp, 
			unsigned int maxHP);
	~scoreBoard();
	HPbar * getMyHQHPbar();
	HPbar * getTheirHQHPbar();


private:
	avatarRoundHP * myAvatar_f;		//Puntero al objeto usado para dibujar los avatars ya formateados
	avatarRoundHP * theirAvatar_f;

	HPbar * myHQHPbar;					//Puntero a la barra de HP del HQ
	HPbar * theirHQHPbar;
	float HPbarMargin;				//Margen alrededor de las barras de HP
	std::string HPbarTitle;			//Frase que va en el medio de las dos HPbars
	ALLEGRO_FONT * font;			//Font para HPbarTitle
	unsigned int HPbarTitleLength;	//Largo en pixeles de HPbarTitle dibujaa con font

	ALLEGRO_BITMAP * myAvatarBmp;	//Puntero al bitmap sin tamanio y forma modificados.
	ALLEGRO_BITMAP * theirAvatarBmp;

	virtual void drawContent();
	virtual void resizeContent();
};

