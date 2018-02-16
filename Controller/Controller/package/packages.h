#pragma once
#include "genericPackage.h"
#include"../../Point.h"
#include"../../Game model/types.h"
#include <iostream>
//*********tipos de paquetes de datos
#define ACK 0X01
#define NAME 0X10
#define NAME_IS 0X11//
#define MAP_IS 0X12//
#define YOU_START 0X20
#define I_START 0X21
#define PASS 0X30
#define MOVE 0X31//
#define PURCHASE 0X32//
#define ATTACK 0X33 //
#define YOU_WON 0X40
#define PLAY_AGAIN 0X50
#define GAME_OVER 0X51
#define ERROR 0XFE
#define QUIT 0XFF

//***********************************

#define PACKAGE_TYPE_POSS 0
#define COUNT_POSS 1

#define SIZE_MOVE_PACKAGE 5	
#define SIZE_ATTACK_PACKAGE 6
#define SIZE_PURCHASE_PACKAGE 5

//**EXTRA BYTES,cantidad bytes que no pertenecen al nombre, pro ejemplo el count y el typo de paquete
#define EXTRA_BYTES_NAME_IS 2 
#define EXTRA_BYTES_MAP_IS 3

//rango columna
#define MIN_COL 0x41
#define MAX_COL 0x50

//rango fila
#define MIN_FIL 0
#define MAX_FIL 0X0C

#define FILA_OR_POS 1
#define FILA_DES_POS 3
#define COL_OR_POS 2
#define COL_DES_POS 4

//purchase package col
#define FILA_POSS_PURCHASE 3
#define COL_POSS_PURCHASE 4
class nameIs :public genericPackage
{
public:
	nameIs(std::string name);
	~nameIs();
	std::string getName() { return this->name;};
private:
	std::string name;
};

class mapIs :public genericPackage
{
public:
	mapIs(std::string mapName, unsigned char checksum);
	~mapIs();
	std::string getMapName() { return mapName;};
	unsigned char getChecksum() { return checksum;};
private:
	std::string mapName;
	unsigned char checksum;
};

class move : public genericPackage
{
public:
	move(unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination);
	move(Point origin, Point destination);
	~move();
	Point getOrigin() { return origin;};
	Point getDestination() { return destination;};
private:
	Point origin;
	Point destination;
};


class attack : public genericPackage
{
public:
	attack(unsigned char dice, unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination);
	attack(unsigned char dice, Point origin, Point destination);
	~attack();
	Point getOrigin() { return origin; };
	Point getDestination() { return destination; };
	unsigned char getDice() { return dice; };
private:
	Point origin;
	Point destination;
	unsigned char dice;
};

class purchase : public genericPackage
{
public:
	purchase(std::string ejercitoID, unsigned char row, unsigned char column);
	purchase(std::string ejercitoID, Point possition);
	~purchase();
	Point getPossition() { return possition; };
	std::string getEjercitoId() { return ejercitoID; };
private:
	Point possition;
	std::string ejercitoID;

};

class ack : public genericPackage
{
public:
	ack();
	~ack();
};
class name :public genericPackage
{
public:
	name();
	~name();
};

class youStart :public genericPackage
{
public:
	youStart();
	~youStart();

};

class iStart : public genericPackage
{
public:
	iStart();
	~iStart();
};

class pass : public genericPackage
{
public:
	pass();
	~pass();
};

class youWon : public genericPackage
{
public:
	youWon();
	~youWon();
};

class playAgain : public genericPackage
{
public:
	playAgain();
	~playAgain();

};

class gameOver :public genericPackage
{
public:
	gameOver();
	~gameOver();
};
class error : public genericPackage
{
public:
	error();
	~error();
};

class quit : public genericPackage
{
public:
	quit();
	~quit();
};