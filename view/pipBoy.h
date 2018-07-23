#pragma once
#include "contentBox.h"
#include "config\pipBoy_config.h"


#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>

#include <vector>
#include <string>


class pipBoy : public contentBox
{
public:
	pipBoy(ALLEGRO_DISPLAY * display, std::vector<std::string> mapPaths);
	~pipBoy();

	void setStatus(pipBoyStatus_t status);	
	void setName(std::string name);	//recibe la parte ya escrita del nombre
	void setIP(std::string ip);	//recibe la parte ya escrita del ip
	void nextMap();
	void previousMap();
	std::string getCurrentMapPath();
	
private:
	pipBoyStatus_t status;
	std::string ip;
	std::string name;
	std::vector<std::string> mapPaths;
	std::vector<ALLEGRO_BITMAP *> mapBmps;
	std::vector<ALLEGRO_BITMAP *>::iterator currentMapBmp;

	ALLEGRO_FONT * font;

	void drawContent();
	void resizeContent();



};
