#pragma once

#include "avatarRoundHP.h"
#include "contentBox.h"

class scoreBoard : public contentBox
{
public:
	scoreBoard(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height,
			ALLEGRO_BITMAP * myAvatar, ALLEGRO_BITMAP * theirAvatar, 
			unsigned int maxHP, ALLEGRO_COLOR scoreColor);
	//max height es width/4 para los dos constructores.
	~scoreBoard();

private:
	avatarRoundHP * myHP;
	avatarRoundHP * theirHP;

	ALLEGRO_BITMAP * myAvatar;		//puntero al bitmap sin tamanio y forma modificados.
	ALLEGRO_BITMAP * theirAvatar;	//idem myAvatar

	virtual void drawContent();
	virtual void resizeContent();
};

