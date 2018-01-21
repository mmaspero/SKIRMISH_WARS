#pragma once
#include"servidor.h"
#include"cliente.h"
#include <iostream>
#include "port-ip.h"
#include"myTimer.h"

typedef enum { CONNECTED, _ERROR, CONECTION_LOST,IN_CONECTION_STAGE_CLIENT,IN_CONECTION_STAGE_SERVER}netState;

class  network
{
public:
	 network(ip ipNumber, port portNumber);
	 netState getCurrentState() { return currentState; };
	 void tryToConect();
	 bool imClient() { return this->imclient; };

	 int reciveData(char * buffer, int bufferSize);
	 //sendData()
	 //recive un arreglo de char, que son lo elementos que mandara. tambien recive
	 //un int con la cantidad de elementos que se necesitan enviar
	 //devuelve false si no se pudo enviar la infromcaion, esto ocurre si hubo un error entre cliente y servidor
	 bool sendData(char * dataToSend, int sizeDataToSend);
	 ~ network();


private:
	myTimer timer;
	bool imclient;
	ip ipNumber;
	port portNumber;
	servidor * server;
	cliente * client;
	netState currentState;

};

