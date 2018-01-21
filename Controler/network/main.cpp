#include"servidor.h"
#include"cliente.h"
#include "myTimer.h"
#include "network.h"
#include <iostream>
#define PORT 13225
int main(void)
{
	network net(ip("localhost"), port(PORT));
	
	while (net.getCurrentState() != CONNECTED)
	{
		net.tryToConect();
	}
	
	if (net.imClient())
	{
		std::cout << "coneccion lograda soy cliente" << std::endl;
	}
	else
	{
		std::cout << "coneccion lograda soy server" << std::endl;
	}
	for (int i = 0; i < 10; i++)
	{
		net.sendData("Piolasa", 8);
	}
	

}


/*cliente tst;
while (!(tst.ConectToServer("localhost", "13225")))
{

}

std::cout << "coneccion lograda" << std::endl;*/




/*myTimer tst(5000);
while (!tst.timeOut())
{

}
std::cout << "ya paso el tiempo" << std::endl;*/

//char buff[100];
//cliente client;
//client.ConectToServer("localhost", "13225");
//client.receiveDataForServidor(buff, 100);
//
/*servidor server(PORT);
while (true)
{
server.ClientIsConected();
}*/



//
//char * data = "Te conectaste al server";
//servidor server(PORT);
//std::cout << "Espero coneccion del cliente" << std::endl;
//server.waitForCliente();
//server.sendData(data, 24);
//std::cout << "Se encio la data" << std::endl;
