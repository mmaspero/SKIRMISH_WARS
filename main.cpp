#include<iostream>
#include"Game model\Model.h"
#include"Controller\controller.h"
#include"view\gui.h"
#include"Controller\eventSource\networkEventSource.h"
#include"Controller\eventSource\userInpuEvSource.h"
#include"Controller\eventSource\eventGenerator.h"
#include"Controller\eventSource\eventSource.h"
#include"initGame.h"
#include "Controller\eventSource\timerEvSource.h"

void main(void)
{
	initGame setUp;
	gui * g=NULL;
	eventGenerator eg;
	network * net = NULL;
	std::string namePlayer;
	Model * m = NULL;
	Controller * c = NULL;
	userInputEvSource * uis = NULL;
	networkEventSource * nes = NULL;
	if (setUp.startGame())
	{
		
		net = setUp.getNet();
		namePlayer = setUp.getName();
		setUp.~initGame();
		g = new gui();
		g->draw();
		m=new Model("Maps/WaterWorld.csv", USER, &(eg.eventQueue), g);
		c = new Controller(net, g, m, &eg);
		uis = new userInputEvSource(g->getDisplay(), g, m);
		nes = new networkEventSource(net, m);
		eg.addEventSource((eventSource *)uis);
		eg.addEventSource((eventSource *)nes);
		eg.addEventSource((eventSource *)c->getTurnTimer());
		g->appendToTextlog("Conexion establecida");
		if (net->imClient())
		{
			g->appendToTextlog("Soy cliente");

		}
		else
		{
			g->appendToTextlog("Soy Server");
		}
		c->run();
	}
	
	
	
	
	//Model m("Maps/WaterWorld.csv", USER, &(eg.eventQueue), &g);
	//network net(ip("localhost"),port(1234));
	//Controller c(&net, &g, &m, &eg);
	//userInputEvSource uis(g.getDisplay(),&g,&m);
	//networkEventSource nes(&net,&m);
	/*eg.addEventSource((eventSource *)(&uis));
	eg.addEventSource((eventSource *)(&nes));
	eg.addEventSource((eventSource *)c.getTurnTimer());*/
	//net.fastConnection(SERVER_N);
	//while (net.getCurrentState() != CONNECTED)
	//{
	//	net.tryToConect();
	//}
	//g.appendToTextlog("Conexion establecida");
	//if (net.imClient())
	//{
	//	g.appendToTextlog("Soy cliente");
	//	
	//}
	//else
	//{
	//	g.appendToTextlog("Soy Server");
	//}
	//c.run();
	

}
