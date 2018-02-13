#include<iostream>
#include"Game model\Model.h"
#include"Controller\controller.h"
#include"view\gui.h"
#include"Controller\eventSource\networkEventSource.h"
#include"Controller\eventSource\userInpuEvSource.h"
#include"Controller\eventSource\eventGenerator.h"
#include"Controller\eventSource\eventSource.h"

void main(void)
{
	gui g;
	g.draw();
	eventGenerator eg;
	Model m("", USER, &(eg.eventQueue), &g);
	network net(ip("localhost"),port(1234));
	Controller c(&net, &g, &m, &eg);
	userInputEvSource uis(g.getDisplay(),&g,&m);
	networkEventSource nes(&net,&m);
	eg.addEventSource((eventSource *)(&uis));
	eg.addEventSource((eventSource *)(&nes));
	c.run();
	

}
