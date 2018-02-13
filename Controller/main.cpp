#include "network\network.h"
#include <iostream>
#include"package\packages.h"
void main()
{
	char * h;
	move tst(1,2,4,4);
	h=tst.getBuff();
	//tst.~move();
	h;
}

//char buff[500];
//network net(ip("localhost"),port(1234));
//while (net.getCurrentState() != CONNECTED)
//{
//	net.tryToConect();
//}
//net.sendData("helo", 5);
//while (true)
//{
//	if ((net.reciveData(buff, 500)) > 0)
//	{
//		std::cout << buff << std::endl;
//	}
//	
//}