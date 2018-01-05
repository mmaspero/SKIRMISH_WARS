#include "avatarRoundHP.h"

#include <algorithm>
#include <allegro5\allegro_primitives.h>

using namespace std;

avatarRoundHP::avatarRoundHP(ALLEGRO_BITMAP * avatar, unsigned int radius, unsigned int maxHP, unsigned int centerX, unsigned int centerY, ALLEGRO_COLOR scoreColor)
{
	if (avatar == nullptr)
	{
		valid = false;	//TODO: que ande con nullptr.
		return;
	}
	unformattedAvatar = avatar;
	setRadius(radius);	//setea radio, offset, y crea el avatar formateado con el radio indicado
	this->centerX = centerX;
	this->centerY = centerY;
	this->maxHP = this->currentHP = maxHP;	//por default se setea la vida al maximo cuando se lo crea
	this->scoreColor = scoreColor;
	transparency = true;
}

avatarRoundHP::~avatarRoundHP()
{
	al_destroy_bitmap(roundAvatar);
}

void avatarRoundHP::draw()
{
	al_draw_filled_circle(centerX, centerY, radius, al_map_rgba_f(0, 0, 0, 0.5));
		
	float currentAngle = 0;
	for (int i = 0; i < currentHP; i++)
	{
		al_draw_arc(centerX, centerY, radius - offset, currentAngle, 2 * ALLEGRO_PI / maxHP - 0.1, scoreColor, offset / 2);	//TODO: magic numbers
		currentAngle += (2 * ALLEGRO_PI / maxHP);
	}
	al_draw_filled_circle(centerX, centerY, radius - 2 * offset, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
	al_draw_bitmap(roundAvatar, centerX - (radius - 3 * offset), centerY - (radius - 3 * offset), 0);	//TODO: magic numbers
}

void avatarRoundHP::setCurrentHP(int currentHP)
{
	this->currentHP = currentHP;
}

int avatarRoundHP::changeHPby(signed int HPchange)
{
	currentHP += HPchange;
	if (currentHP > maxHP)
	{
		currentHP = maxHP;
	}
	else if(currentHP < 0)
	{
		currentHP = 0;
	}
	return currentHP;
}

void avatarRoundHP::setPosition(unsigned int centerX, unsigned int centerY)
{
	this->centerX = centerX;
	this->centerY = centerY;
}

ALLEGRO_COLOR avatarRoundHP::getScoreColor()
{
	return scoreColor;
}

bool avatarRoundHP::isValid()
{
	return valid;
}

unsigned int avatarRoundHP::getRadius()
{
	return radius;
}

void avatarRoundHP::setRadius(int radius)
{
	this->radius = radius;
	offset = (double)radius / 8;	//TODO: magic number
	createRoundAvatar();
}

int avatarRoundHP::getCurrentHP()
{
	return currentHP;
}

void avatarRoundHP::setScoreColor(ALLEGRO_COLOR scoreColor)
{
	this->scoreColor = scoreColor;
}

bool avatarRoundHP::getTransparency()
{
	return transparency;
}

void avatarRoundHP::setTransparency(bool transparency)
{
	this->transparency = transparency;
}

void avatarRoundHP::createRoundAvatar()
{
	if (unformattedAvatar != nullptr)
	{
		//hacer backup del blender y del target bitmap actuales
		int op, src, dst;
		al_get_blender(&op, &src, &dst);	//TODO: hacer backup sin el separate blender del alpha
		ALLEGRO_BITMAP * targetBmpBackup = al_get_target_bitmap();

		roundAvatar = al_create_bitmap((radius - 3 * offset) * 2, (radius - 3 * offset) * 2);
		al_set_target_bitmap(roundAvatar);

		//Esta configuracion de colores sirve como "mascara" para despues quedarse solo con un circulo de lo que sea que se le dibuje arriba
		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);	//sirve para que se mantenga la transparencia del circulo dibujado
		al_draw_filled_circle(radius - 3 * offset, radius - 3 * offset, radius - 3 * offset, al_map_rgba_f(0, 0, 0, 0));	//TODO: magic number

		int w = al_get_bitmap_width(unformattedAvatar), h = al_get_bitmap_height(unformattedAvatar);
		double scalingFactor = (double)(radius - 3 * offset) * 2 / min(w, h);

		//setear blender para que solo se mantenga la parte del avatar que se va a dibujar sobre el circulo. Lo demas es transparente.
		al_set_blender(ALLEGRO_SRC_MINUS_DEST, ALLEGRO_ONE, ALLEGRO_ONE);
		//dibujar de manera que entre toda la imagen en el bitmap sin estirarse
		al_draw_scaled_bitmap(unformattedAvatar, 0, 0, w, h, 0, 0, w * scalingFactor, h * scalingFactor, 0);


		al_set_blender(op, src, dst);
		al_set_target_bitmap(targetBmpBackup);

		//TODO: chequear que con png10 no me anda bien el blending. es demasiado rectangular, y ademas me queda descentrado del circulo
	}
}
