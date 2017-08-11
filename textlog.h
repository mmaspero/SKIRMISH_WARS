#pragma once

#include "contentBox.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <list>
#include <vector>
#include <string>


class textlog : public contentBox
{
public:
	textlog(ALLEGRO_DISPLAY * display);
	~textlog();
	void append(std::string newMsg);
	void append(char* newMsg);
	void clear();

private:
	std::list<std::vector<std::string>> log;
	unsigned int maxLines;	//maxima cantidad de lines que entra en el textlog
	double lineHeight;		//alto de cada renglon. Depende de la fuente elegida
	ALLEGRO_FONT * font;
	ALLEGRO_COLOR fontColor;

	virtual void drawContent();		//dibujar el contenido del Box.
	virtual void resizeContent();
};

