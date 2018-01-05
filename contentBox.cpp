#include "contentBox.h"

#include <allegro5\allegro_primitives.h>
#include <algorithm>
#include "config/contentBox_config.h"

using namespace std;


void drawFunkyRectangle(int x1, int y1, int x2, int y2); //TODO: no entregar una funcion con este nombre



contentBox::contentBox(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height, bool isBoxTransparent)
{
	if (display == nullptr)
	{
		valid = false;
	}
	else
	{
		valid = true;
		this->display = display;
		this->isBoxTransparent = isBoxTransparent;

		palette.background = DEFAULT_BACKGROUND_COLOR;			//TODO: estaria bueno hacerlo de manera menos chota. Con archivo de configuraciones?
		palette.frameBase = DEFAULT_FRAME_BASE_COLOR;
		palette.frameHighlight = DEFAULT_FRAME_HIGHLIGHT_COLOR;

		relativeBoxStartX = startX;
		relativeBoxStartY = startY;
		relativeBoxWidth = width;
		relativeBoxHeight = height;

		setDimensions();
	}
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
	if (!isBoxTransparent)
	{
		drawBox();
	}
	al_set_clipping_rectangle(contentStartX, contentStartY, contentWidth, contentHeight);
	drawContent();
	al_reset_clipping_rectangle();
	
	al_flip_display();	//TODO: decidir si hacemos al_flip_display o nos dedicamos a resolver lo de flipear por sectores
}

void contentBox::acknowledgeResize()
{
	setDimensions();
	resizeContent();
}

bool contentBox::isValid()
{
	return valid;
}

void contentBox::drawBox()
{

	//Dibujar el fondo
	al_draw_filled_rounded_rectangle(relativeBoxStartX * displayWidth + DISPLAY_SECTION_MARGIN, 
									 relativeBoxStartY * displayHeight + DISPLAY_SECTION_MARGIN, 
									(relativeBoxStartX + relativeBoxWidth) * displayWidth - DISPLAY_SECTION_MARGIN, 
									(relativeBoxStartY + relativeBoxHeight) * displayHeight - DISPLAY_SECTION_MARGIN, 
									 CORNER_ROUNDNESS, CORNER_ROUNDNESS, palette.background);	

	//Dibujar frame
	al_draw_rounded_rectangle(relativeBoxStartX * displayWidth + DISPLAY_SECTION_MARGIN,
							  relativeBoxStartY * displayHeight + DISPLAY_SECTION_MARGIN,
							 (relativeBoxStartX + relativeBoxWidth) * displayWidth - DISPLAY_SECTION_MARGIN,
							 (relativeBoxStartY + relativeBoxHeight) * displayHeight - DISPLAY_SECTION_MARGIN,
							  CORNER_ROUNDNESS, CORNER_ROUNDNESS, palette.frameBase, FRAME_WIDTH);
	
	//Dibujar highlight del frame
	al_draw_rounded_rectangle(relativeBoxStartX * displayWidth + DISPLAY_SECTION_MARGIN,
							  relativeBoxStartY * displayHeight + DISPLAY_SECTION_MARGIN,
							 (relativeBoxStartX + relativeBoxWidth) * displayWidth - DISPLAY_SECTION_MARGIN,
							 (relativeBoxStartY + relativeBoxHeight) * displayHeight - DISPLAY_SECTION_MARGIN,
							  CORNER_ROUNDNESS, CORNER_ROUNDNESS, palette.frameHighlight, FRAME_HIGHLIGHT_WIDTH);
}

void contentBox::setDimensions()
{
	displayHeight = al_get_display_height(display);
	displayWidth = al_get_display_width(display);

	//calculo dimensiones para los limites del contenido
	contentStartX = relativeBoxStartX * displayWidth + DISPLAY_SECTION_MARGIN + CONTENT_MARGIN;
	contentStartY = relativeBoxStartY * displayHeight + DISPLAY_SECTION_MARGIN + CONTENT_MARGIN;
	contentWidth = relativeBoxWidth * displayWidth - 2 * (CONTENT_MARGIN + DISPLAY_SECTION_MARGIN);
	contentHeight = relativeBoxHeight * displayHeight - 2 * (CONTENT_MARGIN + DISPLAY_SECTION_MARGIN);
}

void drawFunkyRectangle(int x1, int y1, int x2, int y2)
{
	ALLEGRO_VERTEX v[] = {
		{ x1, y1, 0, 128, 0, al_map_rgb_f(1, 0, 0) },
		{ x2, y1, 0, 256, 256, al_map_rgb_f(0, 0, 1) },
		{ x2, y2, 0, 0, 256, al_map_rgb_f(0, 1, 0) },
		{ x1, y2, 0, 256, 256, al_map_rgb_f(0, 1, 1) } };
	al_draw_prim(v, nullptr, al_load_bitmap("media/img/paperTexture.png"), 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN); //TODO: corregir esta cabeceada del al_load_bitmap
}