#pragma once
#include <iostream>
#include <ctime>
class myTimer
{
public:

	myTimer(unsigned int miliseconds=0);
	~myTimer();
	//setNewTime 
	//recive el nuevo tiempo a setear el timer en milisegundos
	//
	void setNewTime(unsigned int miliseconds);

	//resetTime
	//resetea el timer con el ultimo tiempo seteado
	//
	void resetTime();

	//timeOut
	//devuelve true si el tiempo seteado ya ha ocurrido
	//
	bool timeOut();

	//devuelve cuanto tiempo falta para el time out en milisegundos
	//

	unsigned int restTime();

private:
	unsigned int miliseconds;//timepo entre initialTime y finalTime
	clock_t finalTime;

};

