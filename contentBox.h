#pragma once

#include "allegro5\allegro.h"
#include <string>


//TODO: idea. bool frameless??

struct boxPalette_t {
	ALLEGRO_COLOR background;
	ALLEGRO_COLOR frameBase;
	ALLEGRO_COLOR frameHighlight;
};


class contentBox
{
public:
	contentBox(ALLEGRO_DISPLAY * display);
	~contentBox();
	void setPalette(boxPalette_t palette);
	boxPalette_t getPalette();
	void draw();
	void acknowledgeResize();

protected:

	ALLEGRO_DISPLAY * display;

	double boxStartX;	//esquina superior derecha, coordenada X
	double boxStartY;	//esquina superior izquierda, coordenada Y
	double boxWidth;
	double boxHeight;

	double contentStartX;	//esquina superior derecha, coordenada X
	double contentStartY;	//esquina superior derecha, coordenada Y
	double contentWidth;
	double contentHeight;

	void drawBox();
	virtual void drawContent() = 0;		//dibujar el contenido del Box.
	virtual void resizeContent() = 0;	//reformatear el contenido en respuesta a un cambio de tamanio de display

	void setDimensions();
	boxPalette_t palette;
};