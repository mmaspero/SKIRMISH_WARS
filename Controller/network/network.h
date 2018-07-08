#pragma once
#include"servidor.h"
#include"cliente.h"
#include <iostream>
#include "port-ip.h"
#include"myTimer.h"

typedef enum {  CONNECTED, //la coneccion se completo con exito
			 	   _ERROR,//se ha producido un error en la comunicacion
   	       CONECTION_LOST,//
IN_CONECTION_STAGE_CLIENT,//etapa de intentar conectarse con un servidor
IN_CONECTION_STAGE_SERVER,//etapa de intewntar conectarse con un cliente
N_NET_STATE}netState;

typedef enum {SERVER_N,CLIENT_N}connectionMode;
class  network
{
public:
	 network(ip ipNumber, port portNumber);
	 /*getCurrentState
	 devuelve el estado actual de la red*/
	 netState getCurrentState() { return currentState; };
	 /*tryToConect
	 intenta generar la coneccion, tanto con un servidor como con un cliente,
	 pra saver si la coneccion se logro con exito, se deve llamar a getCurrentState(), y esete
	 deve devolver CONNECTED*/
	 void tryToConect();
	 bool imClient() { return this->imclient; };

	 /*reciveData
	 recive un arreglo de chars y el tamaño de dicho arreglo ,en donde se almacenara la informacion recivida,
	 devuelve MY_ERROR si hubo un error en la recepcion de la informacion,deveulve cero si no recivio nada, sino devuelve la
	 cantidad de informacion que recivio*/
	 int reciveData(char * buffer, int bufferSize);
	 
	 /*sendData()
	 recive un arreglo de char, que son lo elementos que mandara. tambien recive
	 un int con la cantidad de elementos que se necesitan enviar
	 devuelve false si no se pudo enviar la infromcaion, esto ocurre si hubo un error entre cliente y servidor*/
	 bool sendData(char * dataToSend, int sizeDataToSend);
	 ~ network();

	 bool fastConnection(connectionMode mode);


private:
	myTimer timer;
	bool imclient;
	ip ipNumber;
	port portNumber;
	servidor * server;
	cliente * client;
	netState currentState;

};

