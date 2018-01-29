#include "drawingFunctions.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

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
	ALLEGRO_COLOR transparent = al_map_rgba_f(1, 1, 1, 1);
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

ALLEGRO_BITMAP * cropToCircle(ALLEGRO_BITMAP * bmp, float sourceRadius, float destinationRadius, 
	float sourceCenterX, float sourceCenterY)
{
	if (bmp == nullptr)
	{
		return nullptr;
	}
	else
	{
		//hacer backup del blender y del target bitmap actuales
		int op, src, dst;
		al_get_blender(&op, &src, &dst);	//TODO: hacer backup sin el separate blender del alpha
		ALLEGRO_BITMAP * targetBmpBackup = al_get_target_bitmap();

		ALLEGRO_BITMAP * roundBmp = al_create_bitmap(destinationRadius * 2, destinationRadius * 2);
		al_set_target_bitmap(roundBmp);

		//Esta configuracion de colores sirve como "mascara" para despues quedarse solo con un circulo de lo que sea que 
		//se le dibuje arriba
		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);	//sirve para mantener la transparencia del circulo dibujado
		al_draw_filled_circle(destinationRadius, destinationRadius, destinationRadius, al_map_rgba_f(0, 0, 0, 0));	//TODO: magic number

		int w = al_get_bitmap_width(bmp), h = al_get_bitmap_height(bmp);
		float scalingFactor = destinationRadius / sourceRadius;


		//setear blender para que solo se mantenga la parte de bmp que se va a dibujar sobre el circulo. 
		//Lo demas es transparente.
		al_set_blender(ALLEGRO_SRC_MINUS_DEST, ALLEGRO_ONE, ALLEGRO_ONE);
		//dibujar de manera que coincida sourceCenterX y sourceCenterY con el centro de roundBmp
		al_draw_scaled_bitmap(bmp, sourceCenterX - sourceRadius , sourceCenterY - sourceRadius, w, h,
			0, 0, w * scalingFactor, h * scalingFactor, 0);

		//Reestablecer el blender y el target bitmap iniciales
		al_set_blender(op, src, dst);
		al_set_target_bitmap(targetBmpBackup);

		return roundBmp;
		//TODO: chequear que con png10 no me anda bien el blending. es demasiado rectangular, y ademas me queda descentrado del circulo
	}
}

void drawFittingText(ALLEGRO_FONT * font, ALLEGRO_COLOR color, unsigned int row, unsigned int col, const char * text,
	unsigned int maxWidth)
{	
	unsigned int w = al_get_text_width(font, text);
	if (w < maxWidth)
	{
		al_draw_text(font, color, row, col, 0, text);
	}
	else
	{
		al_draw_justified_text(font, color, row, row + maxWidth, col, 1.0, 0, text);
	}
}
