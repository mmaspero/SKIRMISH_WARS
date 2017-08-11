#include "textlog.h"
#include <iostream>

using namespace std;


bool multilineCB(int line_num, const char *line, int size, void *usefulInfo);

struct cbInfo_t {
	vector<string> * formattedMsg;
	unsigned int maxLines;
};


textlog::textlog(ALLEGRO_DISPLAY * display) : contentBox(display)
{
	if (!(font = al_load_ttf_font("Pacifico.ttf", 20, 0)))
	{
		cout << "font no se cargo" << endl;		//TODO: control de error
	}

	lineHeight = al_get_font_line_height(font);
	fontColor = al_map_rgb_f(1, 1, 1);
}

textlog::~textlog()
{
	al_destroy_font(font);
	clear();
}

void textlog::append(std::string newMsg)
{
	newMsg = " >> " + newMsg;

	vector<string> formattedMsg;

	cbInfo_t usefulInfo = { &formattedMsg, maxLines };
	al_do_multiline_text(font,			//TODO: esto se repite en otro lado, unir en una sola funcion
		contentWidth,
		newMsg.c_str(),
		multilineCB,
		(void *)&usefulInfo);

	log.push_back(formattedMsg);
}

void textlog::append(char * newMsg)
{
	append(string(newMsg));
}

void textlog::clear()
{
	log.clear();
}

void textlog::drawContent()
{
	unsigned int remainingLines = maxLines;

	for (list<vector<string>>::reverse_iterator currentMsg = log.rbegin(); //recorre los mensajes dentro de la lista
		currentMsg != log.rend() && remainingLines > 0;
		++currentMsg)			//TODO: se podra acortar este for? es medio feo
	{

		for (unsigned int i = 0;	//recorre las lineas dentro de un mensaje
			remainingLines > 0 && i < (*currentMsg).size();
			++i, --remainingLines)
		{
			al_draw_text(font, fontColor,
				contentStartX, contentStartY + contentHeight - (maxLines - remainingLines + 1) * lineHeight,
				ALLEGRO_ALIGN_LEFT,
				(*currentMsg)[(*currentMsg).size() - 1 - i].c_str());	//TODO: algo, es horrible.
		}
	}
}

void textlog::resizeContent()
{
	list<vector<string>> newLog;

	for (list<vector<string>>::iterator currentMsg = log.begin(); currentMsg != log.end(); ++currentMsg)
	{
		vector<string> formattedMsg;
		string msg("");

		unsigned int lines = (*currentMsg).size();

		for (unsigned int i = 0; i < lines; ++i)
		{
			msg += (*currentMsg)[i];
			if (i + 1 < lines)
			{
				msg += " ";
			}
		}

		cbInfo_t usefulInfo = { &formattedMsg, maxLines };
		al_do_multiline_text(font,
			contentWidth,
			msg.c_str(),
			multilineCB,
			(void *)&usefulInfo);

		newLog.push_back(formattedMsg);
	}
	log = newLog;

	maxLines = contentHeight / lineHeight;
}
