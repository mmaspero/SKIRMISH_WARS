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

#include "config\gui_config.h"

#include "drawingFunctions.h"
#include "paths.h"

#define DEGARAD(n) ((n)*2.0*ALLEGRO_PI/360.0)

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


	{

		//unsigned int n = 5;
		//unsigned int radius = 200;
		//float paso = DEGARAD(0.7);	//giro del circulo en radianes.

		//const ALLEGRO_TRANSFORM * t_backup = al_get_current_transform();
		//ALLEGRO_TRANSFORM t;
		//al_clear_to_color(al_map_rgb_f(1,1,1));

		//for (int j = 0; ; j++)
		//{
		//	al_clear_to_color(al_map_rgb_f(1, 1, 1));
		//	{
		//		//hacer backup del blender y del target bitmap actuales
		//		int op, src, dst;
		//		al_get_blender(&op, &src, &dst);	//TODO: hacer backup sin el separate blender del alpha
		//											//Esta configuracion de colores sirve como "mascara" para despues quedarse solo con un circulo de lo que sea que 
		//											//se le dibuje arriba
		//		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		//		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);	//sirve para mantener la transparencia del circulo dibujado

		//		for (int i = 0; i < n; i++)
		//		{
		//			al_identity_transform(&t);
		//			al_rotate_transform(&t, j * paso + 2 * ALLEGRO_PI* i / n);
		//			al_translate_transform(&t, al_get_display_width(display) / 2.0, al_get_display_height(display) / 2.0);
		//			al_use_transform(&t);
		//			al_draw_filled_circle(radius, 0, 70, al_map_rgba_f(0, 0, 0, 0));
		//			al_identity_transform(&t);
		//			al_use_transform(&t);
		//		}

		//		//setear blender para que solo se mantenga la parte de bmp que se va a dibujar sobre el circulo. 
		//		//Lo demas es transparente.
		//		al_set_blender(ALLEGRO_SRC_MINUS_DEST, ALLEGRO_ONE, ALLEGRO_ONE);
		//		//dibujar de manera que coincida sourceCenterX y sourceCenterY con el centro de roundBmp


		//		
		//		//al_draw_filled_rectangle(0, 0, 1000, 1000, al_map_rgb_f(1, 1, 0));
		//		drawGradientRectangle(  al_get_display_width(display) / 2.0 - 250, 
		//								al_get_display_height(display) / 2.0 - 250, 
		//								al_get_display_width(display) / 2.0 + 250, 
		//								al_get_display_height(display) / 2.0 + 250, 
		//								al_map_rgb_f(1, 0, 0), 
		//								al_map_rgb_f(0, 1, 0), 
		//								al_map_rgb_f(0, 0, 1), 
		//								al_map_rgb_f(1, 0, 1) );

		//		//Reestablecer el blender y el target bitmap iniciales
		//		al_set_blender(op, src, dst);
		//		//al_set_target_bitmap(targetBmpBackup);

		//		//al_draw_bitmap(roundBmp, 0, 0, 0);
		//	}
		//	al_flip_display();
		//	al_rest(0.03);
		//}
	}


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
	
	//Si no se pudo crear correctamente el tileButton, indicar que hubo error
	tileButton * tileButtonP = boardP->getTileButton(tileRow, tileCol);
	if(tileButtonP == nullptr || !tileButtonP->isValid())	//por lazy, solo se llama la funcion si se creo el tileButton
	{
		cout << "No se pudo crear tileObserver en (row,col) = (" << tileRow << "," << tileCol << ") ya que no se pudo crear el boton en esta posicion" << endl;
		return nullptr;
	}

	//Crear tile observer y devolver si no hubo error. Sino se crea correctamente, indicar que hubo error
	tileObserver * to = new tileObserver(t, boardP->getTileButton(tileRow, tileCol), toolboxP);
	if (to->isValid())
	{
		return to;
	}
	else
	{
		return nullptr;
	}
}

playerObserver * gui::playerObserverFactory(Player * p)
{
	list<contentBox *>::iterator itScoreboard = displaySections.begin();
	list<contentBox *>::iterator itToolbox = displaySections.begin();
	list<contentBox *>::iterator itGameStatus = displaySections.begin();


	//Avanzar hasta que se halle el Scoreboard * o hasta recorrer toda la lista.
	for (itScoreboard = displaySections.begin();
		itScoreboard != displaySections.end() && (*itScoreboard)->getType() != SCOREBOARD;
		itScoreboard++) {}

	//Avanzar hasta que se halle el Toolbox * o hasta recorrer toda la lista.
	for (itToolbox = displaySections.begin();
		itToolbox != displaySections.end() && (*itToolbox)->getType() != TOOLBOX;
		itToolbox++) {}

	//Avanzar hasta que se halle el Toolbox * o hasta recorrer toda la lista.
	for (itGameStatus = displaySections.begin();
		itGameStatus != displaySections.end() && (*itGameStatus)->getType() != GAMESTATUS;
		itGameStatus++) {
	}

	//TODO: chequear que los iteradores no esten en end();

	//Crear player observer y devolver si no hubo error. Sino se crea correctamente, indicar que hubo error
	playerObserver * po = new playerObserver(p, (scoreBoard *)(*itScoreboard), (toolbox *)(*itToolbox), (gameStatus*)(*itGameStatus));
	if (po->isValid())
	{
		return po;
	}
	else 
	{
		return nullptr;
	}
}

eventObserver * gui::eventObserverFactory(GenericEvent ** e)	//TODO: hacer puntero a puntero a evento
{
	eventObserver * eo = new eventObserver(e, this);
	if (eo->isValid())
	{
		return eo;
	}
	else
	{
		return nullptr;
	}
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

ALLEGRO_EVENT_SOURCE * gui::getDisplayEventSource()
{
	if (display == nullptr)
	{
		cout << "No se puede obtener el display event source porque display es nullptr" << endl;
	}
	return al_get_display_event_source(display);
}

ALLEGRO_EVENT_SOURCE * gui::getMenuEventSource()
{
	if (display == nullptr)
	{
		cout << "No se puede obtener el menu event source porque display es nullptr" << endl;
	}
	else
	{
		//TODO: googlear como era esto. No tengo internet :(
	}
	return nullptr;
}

void gui::draw()
{
	al_clear_to_color(GUI_DEFAULT_BACKGROUND_COLOR);	//TODO: magic number

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
	draw();
}

contentBox * gui::getDisplaySection(displaySection_t displaySection)
{
	list<contentBox *>::iterator it = displaySections.begin();

	//Avanzar hasta que se halle el Scoreboard * o hasta recorrer toda la lista.
	for (it = displaySections.begin();
		it != displaySections.end() && (*it)->getType() != displaySection;
		it++) {}
	if (it == displaySections.end())
	{
		return nullptr;
	}
	else
	{
		return (*it);
	}
}

void gui::appendToTextlog(const char * msg)
{
	list<contentBox *>::iterator it = displaySections.begin();

	//Avanzar hasta que se halle el textlog * o hasta recorrer toda la lista.
	for (it = displaySections.begin();
		it != displaySections.end() && (*it)->getType() != TEXTLOG;
		it++) {}
	if (it != displaySections.end())	//Si se encontro el textlog
	{
		((textlog *)(*it))->append(msg);
		((textlog *)(*it))->draw();
	}
}

void gui::appendToTextlog(std::string msg)
{
	appendToTextlog(msg.c_str());
}

void gui::setTimeLeft(unsigned int timeLeft)
{
	//TODO:
}

