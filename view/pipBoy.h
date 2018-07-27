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
	pipBoyStatus_t getStatus();
	std::string getIP();
	std::string getName();
	void nextMap();
	void previousMap();
	std::string getCurrentMapPath();
	bool dispatch(int allegroKeycode);
	
private:

	bool dispatchTryingIP(int allegroKeycode);
	bool dispatchInsertingName(int allegroKeycode);

	pipBoyStatus_t status;
	std::string myIP[4];
	int currentByte = 0;	//Proximo byte en el que se tiene que escribir (de 0 a 3)
	int currentChar = 0;	//Proximo caracter en el que se tiene que escribir dentro del byte (0 a 2)

	std::string name;

	std::vector<std::string> mapPaths;
	std::vector<ALLEGRO_BITMAP *> mapBmps;
	std::vector<ALLEGRO_BITMAP *>::iterator currentMapBmp;

	ALLEGRO_FONT * font;

	ALLEGRO_BITMAP * getMapBmp(std::string mapPath);

	void drawContent();
	void resizeContent();



};
