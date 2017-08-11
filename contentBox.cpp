#include "contentBox.h"

#include <allegro5\allegro_primitives.h>


//TODO: decidir donde va la informacion que esta en los defines de aca abajo
#define TEXTLOG_W_START	0.5
#define TEXTLOG_W_END	1.0
#define TEXTLOG_H_START	0
#define TEXTLOG_H_END	1.0
#define TEXTLOG_MARGIN	7.0		//margen entre el verdadero inicio de la caja del textbox y los limites del texto

#define DISPLAY_SECTION_MARGIN 15.0	//margen para la "caja" que contiene todos los elementos del display
									//EJ.: en un display de ancho 600, si dice que la ubicacion de un elemento
									//del display va entre 300 a 600, en realidad, va entre:
									//(300 + DISPLAY_SECTION_MARGIN) y (600 - DISPLAY_SECTION_MARGIN)

contentBox::contentBox(ALLEGRO_DISPLAY * display)
{
	this->display = display;

	palette.background = al_map_rgb(0, 0, 0);			//TODO: estaria bueno hacerlo de manera menos chota
	palette.frameBase = al_map_rgb_f(0.5, 0.5, 0.5);
	palette.frameHighlight = al_map_rgba_f(1, 1, 1, 0.5);

	setDimensions();
}

contentBox::~contentBox()
{
}

void contentBox::setPalette(boxPalette_t palette)
{
	this->palette = palette;
}

boxPalette_t contentBox::getPalette()
{
	return palette;
}

void contentBox::draw()
{
	drawBox();
	drawContent();
	al_flip_display();	//TODO: decidir si hacemos al_flip_display o nos dedicamos a resolver lo de flipear por sectores
}

void contentBox::acknowledgeResize()
{
	setDimensions();
	resizeContent();
	//TODO: draw()? o no lo ponemos aca?
}

void contentBox::drawBox()
{
	//Dibujar el fondo
	al_draw_filled_rounded_rectangle(boxStartX, boxStartY, 
									 boxStartX + boxWidth, boxStartY + boxHeight, 
									 5, 5, palette.background);	//TODO: borrar magic number (mismo que abajo)

	//Dibujar frame
	al_draw_rounded_rectangle(boxStartX, boxStartY, 
							  boxStartX + boxWidth, boxStartY + boxHeight, 
							  5, 5, palette.frameBase, 5);	//TODO: borra magic numbers
	al_draw_rounded_rectangle(boxStartX, boxStartY, 
							  boxStartX + boxWidth, boxStartY + boxHeight, 
							  5, 5, palette.frameHighlight, 1);

}

void contentBox::setDimensions()
{
	//calculo dimensiones para los limites de la box
	boxStartX = al_get_display_width(display) * TEXTLOG_W_START + DISPLAY_SECTION_MARGIN;
	boxStartY = al_get_display_height(display) * TEXTLOG_H_START + DISPLAY_SECTION_MARGIN;
	boxWidth = al_get_display_width(display) * TEXTLOG_W_END - boxStartX - DISPLAY_SECTION_MARGIN;
	boxHeight = al_get_display_height(display) * TEXTLOG_H_END - boxStartY - DISPLAY_SECTION_MARGIN;

	//calculo dimensiones para los limites del contenido
	contentStartX = boxStartX + TEXTLOG_MARGIN;
	contentStartY = boxStartY + TEXTLOG_MARGIN;
	contentWidth = boxWidth - 2 * TEXTLOG_MARGIN;
	contentHeight = boxHeight - 2 * TEXTLOG_MARGIN;
}
