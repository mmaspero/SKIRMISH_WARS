#pragma once
#include "contentBox.h"
#include "config\pipBoy_config.h"


#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>

typedef enum{WELCOME, INSERTING_NAME, TRYING_IP, RETRYING_IP, WAITING_CONNECTION}pipBoyStatus_t;

class pipBoy : public contentBox
{
public:
	pipBoy(ALLEGRO_DISPLAY * display);
	~pipBoy();

	void setStatus(pipBoyStatus_t status);	
	void setName(std::string name);	//recibe la parte ya escrita del nombre
	void setIP(std::string ip);	//recibe la parte ya escrita del ip
	
private:
	pipBoyStatus_t status;
	std::string ip;
	std::string name;

	ALLEGRO_FONT * font;

	void drawContent();
	void resizeContent();



};
