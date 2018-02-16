#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#define MY_ERROR -1
#define MY_EMPTY 0
class cliente
{
public:
	cliente();
	~cliente();
	//ConectToServer()
	//metodo que establese la conexion con el servidor
	//recive como paramteros 2 string. el primero, ipserver, es la ip del servidor
	//y el segundo string, portnumber, es el numero del puerto en el cual el servidor
	//esta escuchando.
	//devuelve true si la coneccion se logro, y false en el caso contrario
	bool ConectToServer(const char* ipServer="localhost", const char* portNumber="12345");
	bool sendData(char * dataToSend_t, unsigned int sizeData);
	int receiveDataForServidor(char * buffer_t, int bufferSize);
	int nonBlockinReceiveDataForServer(char * buffer_t, int bufferSize);
private:
	boost::asio::ip::tcp::resolver* clienteResolver;
	boost::asio::ip::tcp::socket* clienteSocket;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::io_service* ioCliente;
};

