#include "drawingFunctions.h"
#include <allegro5\allegro_primitives.h>

//void drawTexturedGradientRectangle(unsigned int topX, unsigned int leftY, unsigned int bottomX, unsigned int rightY, ALLEGRO_COLOR topLeft, ALLEGRO_COLOR topRight, ALLEGRO_COLOR bottomLeft, ALLEGRO_COLOR bottomRight)
//{

//}

void drawTexturedGradientRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY, 
	ALLEGRO_COLOR topLeftColor, ALLEGRO_COLOR topRightColor, ALLEGRO_COLOR bottomLeftColor, ALLEGRO_COLOR bottomRightColor, 
	ALLEGRO_BITMAP * texture, float scaleX, float scaleY)
{
	ALLEGRO_VERTEX v[] = {
	{ leftX,  topY,    0, leftX  * scaleX, topY    * scaleY, topLeftColor },
	{ rightX, topY,    0, rightX * scaleX, topY    * scaleY, topRightColor },
	{ rightX, bottomY, 0, rightX * scaleX, bottomY * scaleY, bottomRightColor },
	{ leftX,  bottomY, 0, leftX  * scaleX, bottomY * scaleY, bottomLeftColor } };
	al_draw_prim(v, nullptr, texture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

void drawTexturedRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY, ALLEGRO_BITMAP * texture, float scaleX, float scaleY)
{
	ALLEGRO_COLOR transparent = al_map_rgba_f(0, 0, 0, 0);
	drawTexturedGradientRectangle(leftX, topY, rightX, bottomY, transparent, transparent, transparent, transparent,
		texture, scaleX, scaleY);
}

//TODO: documentar
void drawGradientRectangle(unsigned int leftX, unsigned int topY, unsigned int rightX, unsigned int bottomY, ALLEGRO_COLOR topLeftColor, ALLEGRO_COLOR topRightColor, ALLEGRO_COLOR bottomLeftColor, ALLEGRO_COLOR bottomRightColor)
{
	drawTexturedGradientRectangle(leftX, topY, rightX, bottomY,
		topLeftColor, topRightColor, bottomLeftColor, bottomRightColor,
		nullptr, 1, 1);
}
