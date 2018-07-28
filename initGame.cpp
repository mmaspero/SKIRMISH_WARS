#include "initGame.h"
#define TIEMPO_MENSAGE_BIENVENIDA_SEC 1.0
#define TIME_OUT_CONECCION_SEC 120
#define GAME_PORT 1234
#include "Controller\network\port-ip.h"

initGame::initGame()
{
	net = NULL;
	guiInitGame = NULL;
	display = NULL;
	okInit = false;
	CEventos = NULL;
	this->ip_ = "0.0.0.0";
	timeOutNet.setTime(TIME_OUT_CONECCION_SEC);
	//********************sacar*******************
	mapPaths.push_back(std::string("Pathpathpath/primerMap.csv"));//hay que sacarrlo
	mapPaths.push_back(std::string("Pathpathpath/segundoMap.csv"));
	mapPaths.push_back(std::string("Pathpathpath/tercerMapXDXDXD.csv"));
	//********************************************
	okInit = allegroInicializacion();
	if (okInit)
	{
		guiInitGame = new pipBoy(display, mapPaths);
	}
}

initGame::~initGame()
{
	if (okInit)
	{
		allegroDestruccion();
		delete guiInitGame;
		
	}
	
	
}

bool initGame::startGame()
{
	bool exitprogram = false;
	bool dispachGui = false;
	bool netNotCreated = true;
	if (!okInit)
	{
		return false;
	}
	guiInitGame->draw();
	al_rest(TIEMPO_MENSAGE_BIENVENIDA_SEC);
	guiInitGame->setStatus(INSERTING_NAME);
	guiInitGame->draw();
	do
	{
		guiInitGame->draw();
		if (!al_is_event_queue_empty(CEventos))
		{
			al_get_next_event(CEventos, &ev);
			if ((ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) || (ev.type ==ALLEGRO_EVENT_DISPLAY_CLOSE))
			{
				exitprogram = true;
			}
			else
			{
				if (ev.type == ALLEGRO_EVENT_KEY_UP)
				{
					dispachGui = guiInitGame->dispatch(ev.keyboard.keycode);
				}
				
			}

		}
		if ((dispachGui && !exitprogram) ||guiInitGame->getStatus()== WAITING_CONNECTION)
		{
			switch (guiInitGame->getStatus())
			{
			case INSERTING_NAME:
				name = guiInitGame->getName();
				guiInitGame->setStatus(TRYING_IP);
				
				break;
			case TRYING_IP:
				this->ip_ = guiInitGame->getIP();
				guiInitGame->setStatus(WAITING_CONNECTION);
				timeOutNet.startTimer();
				break;
			case WAITING_CONNECTION:
				if ((ipOK())&&(timeOutNet.getEvent()==NULL))
				{
					if (netNotCreated)
					{
						this->net = new network(ip(this->ip_), port(GAME_PORT));
						netNotCreated = false;
					}
					else
					{
						net->tryToConect();
						if (net->getCurrentState() == CONNECTED)
						{
							return true;
						}
					}
					
				}
				else
				{
					if (net != NULL)
					{
						delete net;
					}
					exitprogram = true;//la ip no tiene un formato valido o hubo un time out
				}
				break;
			default:
				break;
			}
			dispachGui = false;
		}
	} while (!exitprogram);


	return false;
}

bool initGame::ipOK()
{
	int a, b, c, d;
	if (sscanf(this->ip_.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d) != 4)
	{
		return false;
	}
	if (a > 255 || a < 0 || b>255 || b < 0 || c>255 || c < 0 || d>255 || d < 0)
	{
		return false;
	}

	return true;
}

bool initGame::allegroInicializacion()
{
	if (!al_init()) {
		std::cout << "FALLA AL INICIALIZAR ALLEGRO" << std::endl;
		return false;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "FALLA AL INICIALIZAR primitives_addon" << std::endl;
		return false;

	}
	if (!al_init_font_addon())
	{
		std::cout << "FALLA AL INICIALIZAR font_addon" << std::endl;
		return false;
	}
	if (!al_init_ttf_addon())
	{
		std::cout << "FALLA AL INICIALIZAR ttf_addon" << std::endl;
		return false;
	}
	
	

	display = al_create_display(PIPBOY_DEFAULT_W, PIPBOY_DEFAULT_H);
	if(display==NULL)
	{
		std::cout << "FALLA AL INICIALIZAR DISPLAY" << std::endl;
		return false;
	}
	
	al_install_keyboard();
	CEventos = al_create_event_queue();
	if (CEventos == NULL)
	{
		std::cout << "FALLA AL CREAR event_queue" << std::endl;
		al_destroy_display(display);
		return false;
	}
	al_register_event_source(CEventos, al_get_keyboard_event_source());
	al_register_event_source(CEventos, al_get_display_event_source(display));
	return true;
}

bool initGame::allegroDestruccion()
{
	al_destroy_display(display);
	al_destroy_event_queue(CEventos);
	return false;
}
