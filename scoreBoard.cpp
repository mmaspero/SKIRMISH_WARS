#include "scoreBoard.h"

#define MAX_HP 8	//TODO: mover de aca

scoreBoard::scoreBoard(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height, ALLEGRO_BITMAP * myAvatar, ALLEGRO_BITMAP * theirAvatar, unsigned int maxHP, ALLEGRO_COLOR scoreColor)
	:contentBox(display, startX, startY, width, height, true)
{
	if (valid)
	{
		if (myAvatar != nullptr)
		{
			this->myAvatar = myAvatar;
		}
		if (theirAvatar != nullptr)
		{
			this->theirAvatar = theirAvatar;
		}
		int radius = contentHeight / 2;	//El diametro es toda la altura disponible del contentBox
		myHP = new avatarRoundHP(myAvatar, radius, MAX_HP, 
								contentStartX + radius, contentStartY + radius);
		theirHP = new avatarRoundHP(theirAvatar, radius, MAX_HP, 
								contentStartX + contentWidth - radius, contentStartY + radius);
	}
}

scoreBoard::~scoreBoard()
{

}

void scoreBoard::drawContent()
{
	myHP->draw();
	theirHP->draw();
}

void scoreBoard::resizeContent()
{
	int radius = contentHeight / 2;
	theirHP->setRadius(radius);
	theirHP->setPosition(contentStartX + contentWidth - radius, contentStartY + radius);
	myHP->setRadius(radius);
	myHP->setPosition(contentStartX + radius, contentStartY + radius);
}
