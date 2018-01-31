#include "packages.h"

nameIs::nameIs(std::string name)
{
	type = NAME_IS;
	this->name = name;
}

mapIs::mapIs(std::string mapName, unsigned char checksum)
{
	this->mapName = mapName;
	this->checksum = checksum;
	type = MAP_IS;
}

move::move(unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination)
{
	origin.row = rowOrigin;
	origin.col = columnOrigin;
	destination.row = rowDestination;
	destination.col= columnDestination;
	type = MOVE;
}

move::move(Point origin, Point destination)
{
	this->origin = origin;
	this->destination = destination;
	type = MOVE;
}

attack::attack(unsigned char dice, unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination)
{
	origin.row = rowOrigin;
	origin.col = columnOrigin;
	destination.row = rowDestination;
	destination.col = columnDestination;
	this->dice = dice;
	type = ATTACK;
}

attack::attack(unsigned char dice, Point origin, Point destination)
{
	this->origin = origin;
	this->destination = destination;
	this->dice = dice;
	type = ATTACK;
}

ack::ack()
{
	type = ACK;
}

name::name()
{
	type = NAME;
}

youStart::youStart()
{
	type = YOU_START;
}

iStart::iStart()
{
	type = I_START;

}

pass::pass()
{
	type = PASS;
}

youWon::youWon()
{
	type = YOU_WON;
}

playAgain::playAgain()
{
	type = PLAY_AGAIN;
}

gameOver::gameOver()
{
	type = GAME_OVER;
}

error::error()
{
	type = ERROR;
}

quit::quit()
{
	type = QUIT;
}

purchase::purchase(std::string ejercitoID, unsigned char row, unsigned char column)
{
	this->ejercitoID = ejercitoID;
	this->possition.row = row;
	this->possition.col= column;
	this->type = PURCHASE;
}

purchase::purchase(std::string ejercitoID, Point possition)
{
	this->ejercitoID = ejercitoID;
	this->possition = possition;
	this->type = PURCHASE;
}