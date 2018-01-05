#include <iostream>
#include "textlog.h"
#include "config/textlog_config.h"
#include <allegro5\allegro_primitives.h>
#pragma warning(disable : 4996)	//TODO: !!!!!!!!!!!!!!!!!!!!!!!!!!



using namespace std;


bool multilineCB(int line_num, const char *line, int size, void *usefulInfo);

struct cbInfo_t {
	vector<string> * formattedMsg;
	unsigned int maxLines;
};


textlog::textlog(ALLEGRO_DISPLAY * display, float startX, float startY, float width, float height) 
	: contentBox(display, startX, startY, width, height)
{
	if (valid)	//construye textlog solo si contentBox se pudo construir sin problemas
	{
		if (!(font = al_load_ttf_font(FONT_NAME, FONT_SIZE, 0)))
		{
			cout << "no se cargo font del textlog" << endl;
			valid = false;	//indica que el textlog no se pudo contruir correctamente
		}
		else
		{
			lineHeight = al_get_font_line_height(font);
			maxLinesDisplayed = contentHeight / lineHeight;
			totalLines = 0;
			scrollOffset = 0;
			lineHeader = string(DEFAULT_LINE_HEADER);
			fontColor = DEFAULT_FONT_COLOR;
		}
	}
}

textlog::~textlog()
{
	al_destroy_font(font);
	clear();
}

void textlog::append(std::string newMsg)
{
	newMsg = lineHeader + newMsg;

	vector<string> formattedMsg;

	cbInfo_t usefulInfo = { &formattedMsg, maxLinesDisplayed };
	al_do_multiline_text(font,			//TODO: esto se repite en otro lado, unir en una sola funcion
		contentWidth,
		newMsg.c_str(),
		multilineCB,
		(void *)&usefulInfo);

	log.push_back(formattedMsg);
	totalLines += formattedMsg.size();
}

void textlog::append(char * newMsg)
{
	append(string(newMsg));
}

void textlog::scroll(signed int offset)
{
	if (maxLinesDisplayed >= totalLines)	//Si el textlog no ocupa mas de todo el espacio disponible
	{
		scrollOffset = 0;	//asegurarse que el texto no se mueva
	}
	else	//Si el textlog ocupa mas espacio del disponible (obs: aca, totalLines - maxLinesDisplayed > 0)
	{
		scrollOffset += offset;	

		//control de underflow y overflow : 0 <= scrolloffset <= totalLines - maxLinesDisplayed
		if (scrollOffset < 0)
		{
			scrollOffset = 0;
		}
		else if (scrollOffset > totalLines - maxLinesDisplayed)
		{
			scrollOffset = totalLines - maxLinesDisplayed;
		}
		draw();
	}
}

void textlog::clear()
{
	log.clear();
}

void textlog::drawContent()
{
	unsigned int analysedLines = 0;

	for (list<vector<string>>::reverse_iterator currentMsg = log.rbegin(); //recorre los mensajes dentro de la lista y los dibuja
		currentMsg != log.rend() && analysedLines <= (maxLinesDisplayed + scrollOffset);	//hasta que se terminen los mensajes o no haya mas lugar para dibujar mas lineas
		++currentMsg)	//dibuja un mensaje por iteracion
						//TODO: se podra acortar este for? es medio feo
	{
		for (int i = 0;	//recorre las lineas dentro de un mensaje y las dibuja
			analysedLines <= (maxLinesDisplayed + scrollOffset) && i < (*currentMsg).size();	//hasta que se terminen las lineas o no haya mas lugar para dibujarlas
			++i, ++analysedLines)	//dibuja una linea por iteracion
		{
			if (analysedLines >= scrollOffset)
			{
				al_draw_text(font, fontColor,
					contentStartX, contentStartY + contentHeight - (analysedLines - scrollOffset + 1) * lineHeight,
					ALLEGRO_ALIGN_LEFT,
					(*currentMsg)[(*currentMsg).size() - 1 - i].c_str());	//TODO: algo, es horrible.
				
			}
		}
	}
}

void textlog::resizeContent()
{
	list<vector<string>> newLog;
	totalLines = 0;

	//iterar a traves de todos los mensajes
	for (list<vector<string>>::iterator currentMsg = log.begin(); currentMsg != log.end(); ++currentMsg)
	{
		vector<string> formattedMsg;	
		string msg("");					

		unsigned int oldFormatLines= (*currentMsg).size();	//cant de renglones de cada mensaje antes de reformatearlo

		//iterar a traves de todos los renglones de cada mensaje
		for (unsigned int i = 0; i < oldFormatLines; ++i)
		{
			msg += (*currentMsg)[i];	//uno todos los renglones en un solo string que contenga el mensaje entero
			if (i + 1 != oldFormatLines)	//si el renglon no es el ultimo
			{
				msg += " ";	//despues de todos los renglones menos el ultimo es necesario agregar un espacio
							//por como al_do_multiline_text() genero los strings de cada renglon
			}
		}

		cbInfo_t usefulInfo = { &formattedMsg, maxLinesDisplayed };
		al_do_multiline_text(font,
			contentWidth,
			msg.c_str(),
			multilineCB,
			(void *)&usefulInfo);

		newLog.push_back(formattedMsg);
		totalLines += formattedMsg.size();
	}
	log = newLog;
	maxLinesDisplayed = contentHeight / lineHeight;

	scroll(0);	//de ser necesario, ajusta el offset a las dimensiones y el formato actual
}


bool multilineCB(int line_num, const char * line, int size, void * usefulInfo)
{
	cbInfo_t * info = (cbInfo_t *)usefulInfo;
	char * newLine = strncpy(new char[size + 1], line, size);		//TODO: el arreglo creado se destruye cuando se hace pop_back() o cuando se destruye la lista??
	newLine[size] = '\0';											//TODO: aparentemente strncpy es una verga, que usamos? strlcpy seria la opcion que tira google pero no es estandar o no se, no entiendo nada
	info->formattedMsg->push_back(string(newLine));

	return true;
}