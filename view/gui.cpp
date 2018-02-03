#include "gui.h"

#include <iostream>

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include "scoreBoard.h"
#include "Board.h"
#include "textlog.h"
#include "optionBox.h"
#include "gameStatus.h"

#include "drawingFunctions.h"
#include "paths.h"

#define DEFAULT_SCREEN_W 1200.0f
#define DEFAULT_SCREEN_H 800.0f

#define MIN_SCREEN_W 1024.0f
#define MIN_SCREEN_H  768.0f

using namespace std;

gui::gui()
{
	if (!al_init())
	{
		cout << "No se pudo inicializar Allegro" << endl;
		valid = false;
	}
	else if (!al_init_font_addon())
	{
		cout << "No se pudo inicializar el addon de font" << endl;
		valid = false;
	}
	else if (!al_init_ttf_addon())
	{
		cout << "No se pudo inicializar el addon de ttf" << endl;
		al_shutdown_font_addon();
		valid = false;
	}
	else if (!al_init_primitives_addon())
	{
		cout << "No se pudo inicializar el addon de primitivas" << endl;
		al_shutdown_ttf_addon();
		al_shutdown_font_addon();
		valid = false;
	}
	else if (!al_init_image_addon())
	{
		cout << "No se pudo inicializar el addon de imagenes" << endl;
		al_shutdown_primitives_addon();
		al_shutdown_ttf_addon();
		al_shutdown_font_addon();
		al_shutdown_image_addon();
		valid = false;
	}

	////////////////////////creacion y personalizacion display/////////////////////////////
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	h = DEFAULT_SCREEN_H;
	w = DEFAULT_SCREEN_W;

	if (!(display = al_create_display(w, h)))
	{
		cout << "No se pudo crear el display" << endl;
		valid = false;
	}
	al_set_window_constraints(display, MIN_SCREEN_W, MIN_SCREEN_H, 0, 0);	//TODO: por config
	al_apply_window_constraints(display, true);

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
	ALLEGRO_BITMAP * icon = al_load_bitmap(IMAGE_PATH "myAvatar1.png");	//TODO: sacarlo de config
	if (icon == nullptr)
	{
		//No se pone valid en false ya que el programa puede correr sin el icono de la ventana
		cout << "No se pudo cargar el icono del display" << endl;
	}
	else
	{
		al_set_display_icon(display, icon);
	}
	al_set_window_title(display, "Skirmish Wars");	//TODO: sacarlo de config

	displaySections.push_back((contentBox *) new Board(display, 0, 0.3, 0.7, 0.7));
	if (!displaySections.back()->isValid())
	{
		cout << "No se pudo construir la seccion del display Board" << endl;
		valid = false;
		return;
	}
	
	displaySections.push_back((contentBox *) new scoreBoard(display, 0, 0.1, 0.7, 0.2,
		al_load_bitmap(IMAGE_PATH "myAvatar1.png"), al_load_bitmap(IMAGE_PATH "theirAvatar.png"),
		8, 0, 0, 0));	//TODO: sacar magic numbers, validacion de parametros de ALLEGRO_BITMAP * 
	if (!displaySections.back()->isValid())
	{
		cout << "No se pudo construir la seccion del display ScoreBoard" << endl;
		valid = false;
		return;
	}

	displaySections.push_back((contentBox *) new gameStatus(display, 0, 0, 0.7, 0.1, 0));	
	if (!displaySections.back()->isValid())
	{
		cout << "No se pudo construir la seccion del display gameStatus" << endl;
		valid = false;
		return;
	}

	displaySections.push_back((contentBox *) new textlog(display, 0.7, 0.5, 0.3, 0.5));
	if (!displaySections.back()->isValid())
	{
		cout << "No se pudo construir la seccion del display Textlog" << endl;
		valid = false;
		return;
	}

	displaySections.push_back((contentBox *) new toolbox(display, 0.7, 0, 0.3, 0.5));
//	((toolbox *)displaySections.back())->selectProduct((unit_t)3);	//TODO: volar, es de debug
	if (!displaySections.back()->isValid())
	{
		cout << "No se pudo construir la seccion del display Toolbox" << endl;
		valid = false;
		return;
	}//TODO: controlar que se destruyan todos los contentBoxes de ser que alguno tiene valid = false;

	ALLEGRO_MENU_INFO menu_info[] = {
	ALLEGRO_START_OF_MENU("&Opciones", 1),
		{ "&Mute/Unmute", 2, 0, NULL },	//TODO: hacer que cambie de mute a unmute
		ALLEGRO_START_OF_MENU("Toggle warnings",3),
			{"Before buying", 4, 0, NULL},
			{"Before attacking", 5, 0, NULL},
		ALLEGRO_END_OF_MENU,
		ALLEGRO_MENU_SEPARATOR,
		{ "Quit", 6, 0, NULL },
		ALLEGRO_END_OF_MENU,
	ALLEGRO_END_OF_MENU
	};

	menu = al_build_menu(menu_info);

	if (!(valid = al_set_display_menu(display, menu)))
	{
		cout << "No se pudo anexar el menu al display" << endl;
		valid = false;
		return;
	}
}	//TODO: un control mas cercano de valid

gui::~gui()
{
	al_set_display_menu(display, nullptr);	//destruir el menu

	displaySections.clear();

	al_destroy_display(display);

	al_shutdown_image_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();
}

tileObserver * gui::tileObserverFactory(Tile * t)
{
	if (t == nullptr)
	{
		cout << "No se pudo crear el tileObserver ya que se recibio un nullptr en vez de un Tile *" << endl;
		return nullptr;
	}

	list<contentBox *>::iterator itBoard = displaySections.begin();
	list<contentBox *>::iterator itToolbox = displaySections.begin();

	//Avanzar hasta que se halle el Board * o hasta recorrer toda la lista.
	for (itBoard = displaySections.begin(); 
		itBoard != displaySections.end() && (*itBoard)->getType() != BOARD; 
		itBoard++) {}

	//Avanzar hasta que se halle el Toolbox * o hasta recorrer toda la lista.
	for (itToolbox = displaySections.begin();
		itToolbox != displaySections.end() && (*itToolbox)->getType() != TOOLBOX;
		itToolbox++) {}

	//Si se llego al final de la lista es porque no se encontro la display section buscada
	if (itBoard == displaySections.end() || itToolbox == displaySections.end()) 
	{
		cout << "No se pudo construir el tileObserver porque hay display sections faltantes" << endl;
		return nullptr;
	}
	Board * boardP = (Board *)(*itBoard);
	toolbox * toolboxP = (toolbox *)(*itToolbox);

	unsigned int tileRow = t->getPosition().row;
	unsigned int tileCol = t->getPosition().col;

	//Si ya se creo el tileButton de esa posicion, indicar que hubo error.
	if (boardP->getTileButton(tileRow, tileCol) != nullptr)
	{
		cout << "No se pudo crear tileObserver en (row,col) = (" << tileRow << "," << tileCol <<") porque ya hay un tileObserver para esta tile" << endl;
		return nullptr;
	}
	
	float tileSide = boardP->getTileSide();
	ALLEGRO_BITMAP * tileBmp = al_create_bitmap(tileSide, tileSide);
			
	ALLEGRO_FONT * font = al_load_font(FONT_PATH "ttf.ttf", -tileSide / 4, 0);
	
	boardP->setTileButton(t);
	
	tileButton * tileButtonP = boardP->getTileButton(tileRow, tileCol);
	if(tileButtonP == nullptr || !tileButtonP->isValid())	//por lazy, solo se llama la funcion si se creo el tileButton
	{
		cout << "No se pudo crear tileObserveren (row,col) = (" << tileRow << "," << tileCol << ") ya que no se pudo crear el boton en esta posicion" << endl;
		return nullptr;
	}
	return new tileObserver(t, boardP->getTileButton(tileRow, tileCol), toolboxP);
}

playerObserver * gui::playerObserverFactory(Player * p)
{
	list<contentBox *>::iterator itScoreboard = displaySections.begin();
	list<contentBox *>::iterator itToolbox = displaySections.begin();

	//Avanzar hasta que se halle el Scoreboard * o hasta recorrer toda la lista.
	for (itScoreboard = displaySections.begin();
		itScoreboard != displaySections.end() && (*itScoreboard)->getType() != SCOREBOARD;
		itScoreboard++) {}

	//Avanzar hasta que se halle el Toolbox * o hasta recorrer toda la lista.
	for (itToolbox = displaySections.begin();
		itToolbox != displaySections.end() && (*itToolbox)->getType() != TOOLBOX;
		itToolbox++) {}

	//TODO: validacion de parametros enviados, y validacion de que no haya problemas en el constructor
	return new playerObserver(p, (scoreBoard *)(*itScoreboard), (toolbox *)(*itToolbox));
}

eventObserver * gui::eventObserverFactory(GenericEvent * e)
{
	return new eventObserver(e);
}

bool gui::isValid()
{
	return valid;
}

ALLEGRO_DISPLAY * gui::getDisplay()
{
	return display;
}

button * gui::getButton(unsigned int xPixel, unsigned int yPixel)
{
	contentBox * currentContentBox = getDisplaySection(xPixel, yPixel);
	if (currentContentBox != nullptr)
	{
		return currentContentBox->getButton(xPixel, yPixel);
	}
	else
	{
		return nullptr;
	}
}

contentBox * gui::getDisplaySection(unsigned int xPixel, unsigned int yPixel)
{
	contentBox * contentBoxSelected = nullptr;
	for (list<contentBox *>::iterator it = displaySections.begin(); it != displaySections.end(); it++)
	{
		if ((*it)->isItHere(xPixel, yPixel))
		{
			contentBoxSelected = *it;
		}
	}
	return contentBoxSelected;
}

void gui::draw()
{
	al_clear_to_color({ 1,1,0,1 });

	for (list<contentBox *>::iterator it = displaySections.begin(); it != displaySections.end(); it++)
	{
		(*it)->draw();
	}
}

void gui::acknowledgeResize()
{
	al_acknowledge_resize(display);

	for (list<contentBox *>::iterator it = displaySections.begin(); it != displaySections.end(); it++)
	{
		(*it)->acknowledgeResize();
	}
}
