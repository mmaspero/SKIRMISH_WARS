#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class avatarRoundHP
{
public:
	avatarRoundHP(ALLEGRO_BITMAP * avatar, unsigned int radius, unsigned int maxHP, unsigned int centerX, unsigned int centerY, ALLEGRO_COLOR scoreColor = { 1,0,0,1 });
	~avatarRoundHP();
	void draw();
	bool isValid();
	unsigned int getRadius();
	void setRadius(int radius);
	int getCurrentHP();
	void setCurrentHP(int currentHP);
	int changeHPby(signed int HPchange);
	void setPosition(unsigned int centerX, unsigned int centerY);
	ALLEGRO_COLOR getScoreColor();		//TODO: hace falta??
	void setScoreColor(ALLEGRO_COLOR scoreColor);
	bool getTransparency();
	void setTransparency(bool transparency);

private:
	void createRoundAvatar();
	bool valid;
	unsigned int radius;
	double offset;
	unsigned int centerX;
	unsigned int centerY;
	unsigned int maxHP;
	int currentHP;
	ALLEGRO_COLOR scoreColor;
	ALLEGRO_BITMAP * roundAvatar;
	ALLEGRO_BITMAP * unformattedAvatar;
	bool transparency;	//TODO: documentar
};

