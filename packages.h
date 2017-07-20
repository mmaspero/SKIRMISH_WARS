#pragma once
#include "genericPackage.h"
#include "point.h"
#include <iostream>
//*********tipos de paquetes de datos
#define ACK 0X01
#define NAME 0X10
#define NAME_IS 0X11
#define MAP_IS 0X12
#define YOU_START 0X20
#define I_START 0X21
#define PASS 0X30
#define MOVE 0X31
#define PURCHASE 0X32
#define ATTACK 0X33 
#define YOU_WON 0X40
#define PLAY_AGAIN 0X50
#define GAME_OVER 0X51
#define ERROR 0XFE
#define QUIT 0XFF

//***********************************

class nameIs :public genericPackage
{
public:
	nameIs(std::string name);
	std::string getName() { return this->name;};
private:
	std::string name;
};

class mapIs :public genericPackage
{
public:
	mapIs(std::string mapName, unsigned char checksum);
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
	move(point origin, point destination);
	point getOrigin() { return origin;};
	point getDestination() { return destination;};
private:
	point origin;
	point destination;
};

//falta paquete purchase

class attack : public genericPackage
{
public:
	attack(unsigned char dice, unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination);
	attack(unsigned char dice, point origin, point destination);
	point getOrigin() { return origin; };
	point getDestination() { return destination; };
	unsigned char getDice() { return dice; };
private:
	point origin;
	point destination;
	unsigned char dice;
};

class ack : public genericPackage
{
public:
	ack();
};
class name :public genericPackage
{
public:
	name();
};

class youStart :public genericPackage
{
public:
	youStart();
};

class iStart : public genericPackage
{
public:
	iStart();
};

class pass : public genericPackage
{
public:
	pass();
};

class youWon : public genericPackage
{
public:
	youWon();
};

class playAgain : public genericPackage
{
public:
	playAgain();
};

class gameOver :public genericPackage
{
public:
	gameOver();
};
class error : public genericPackage
{
public:
	error();
};

class quit : public genericPackage
{
public:
	quit();
};