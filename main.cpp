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
#include"getNameMap.h"

void main(void)
{
	initGame setUp;
	gui * g=NULL;
	eventGenerator eg;
	network * net = NULL;
	std::string namePlayer;
	std::string opponentPlayer;
	std::string pathMap;
	Model * m = NULL;
	Controller * c = NULL;
	userInputEvSource * uis = NULL;
	networkEventSource * nes = NULL;
	bool CorrectData = false;
	bool first = false;
	if (setUp.startGame())
	{
		
		net = setUp.getNet();
		namePlayer = setUp.getName();
		setUp.~initGame();
		g = new gui();
		g->draw();
		if (net->imClient())
		{
			g->appendToTextlog("Soy cliente");
			CorrectData = getServerInfo(*net,namePlayer,opponentPlayer, pathMap, first);

		}
		else
		{
			g->appendToTextlog("Soy Server");
			CorrectData = getClientInfo(*net, namePlayer, opponentPlayer, pathMap, first);
		}

		if (CorrectData)
		{
			m = new Model(pathMap.c_str(), (first ? USER : OPPONENT), &(eg.eventQueue), g);
			//	m=new Model("Maps/WaterWorld.csv", OPPONENT, &(eg.eventQueue), g);
			c = new Controller(net, g, m, &eg);
			uis = new userInputEvSource(g->getDisplay(), g, m);
			nes = new networkEventSource(net, m);
			eg.addEventSource((eventSource *)uis);
			eg.addEventSource((eventSource *)nes);
			eg.addEventSource((eventSource *)c->getTurnTimer());
			g->appendToTextlog("Conexion establecida");

			c->run();

		}

		


	
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
