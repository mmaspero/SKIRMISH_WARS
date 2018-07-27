#include <iostream>
#include "Game model\Model.h"
#include "Controller\controller.h"
#include "view\gui.h"
#include "Controller\eventSource\networkEventSource.h"
#include "Controller\eventSource\userInpuEvSource.h"
#include "Controller\eventSource\eventGenerator.h"
#include "Controller\eventSource\eventSource.h" 
#include "view\textlog.h"	//TODO: sacar de aca
#include <allegro5\allegro_primitives.h>	//TODO: sacar de aca

#include "view\pipBoy.h"	//TODO: sacar de aca
#include "view\config\pipBoy_config.h"	//TODO: sacar de aca


void main(void)
{

	{
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	std::vector<std::string> mapPaths;
	mapPaths.push_back(std::string("Pathpathpath/primerMap.csv"));
	mapPaths.push_back(std::string("Pathpathpath/segundoMap.csv"));
	mapPaths.push_back(std::string("Pathpathpath/tercerMapXDXDXD.csv"));


	ALLEGRO_DISPLAY * display = al_create_display(PIPBOY_DEFAULT_W, PIPBOY_DEFAULT_H);

	pipBoy pb(display, mapPaths);
	pb.draw();
	al_rest(1.0);
	pb.setStatus(TRYING_IP);
	pb.draw();

	al_install_keyboard();
	ALLEGRO_EVENT_QUEUE * q = al_create_event_queue();
	al_register_event_source(q, al_get_keyboard_event_source());
	al_register_event_source(q, al_get_display_event_source(display));
	ALLEGRO_EVENT ev;

	std::string name;
	std::string ip;

	bool exitProgram = false;
	pb.setStatus(INSERTING_NAME);
	do
	{
		pb.draw();
		if (!al_is_event_queue_empty(q))
		{
			al_get_next_event(q, &ev);
			if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				if(ev.keyboard.keycode ==  ALLEGRO_KEY_ESCAPE)
				{
					exitProgram = true;
				}
				else
				{
					if(pb.dispatch(ev.keyboard.keycode))
					{
						if (pb.getStatus() == INSERTING_NAME)
						{
							name = pb.getName();
							std::cout << name << std::endl;
							pb.setStatus(TRYING_IP);
						}
						else if (pb.getStatus() == TRYING_IP)
						{
							ip = pb.getIP();
							//si ip es valida
							{
								pb.setStatus(WAITING_CONNECTION);
								//intentarConectar()
								//si se conecto, pipboyDone = true, else exitProgram = true
							}
						}
					}
				}
			} 
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				exitProgram = true;
			}
		}
	} while (!exitProgram);

}


	gui g;
	g.draw();
	eventGenerator eg;
	Model m("Maps/WaterWorld.csv", USER, &(eg.eventQueue), &g);
	network net(ip("localhost"), port(1234));
	Controller c(&net, &g, &m, &eg);
	userInputEvSource uis(g.getDisplay(), &g, &m);
	networkEventSource nes(&net, &m);
	eg.addEventSource((eventSource *)(&uis));
	eg.addEventSource((eventSource *)(&nes));
	net.fastConnection(CLIENT_N);
	//while (net.getCurrentState() != CONNECTED)
	//{
	//	net.tryToConect();
	//}
	g.appendToTextlog("Conexion establecida");
	c.run();
}


//TODO: si no pongo gui.draw(), dibuja igual. Hacer que los constructores no dibujen

