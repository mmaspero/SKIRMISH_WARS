#include "packages.h"
#include<string.h>
nameIs::nameIs(std::string name)
{
	type = NAME_IS;
	this->name = name;
	this->sizeBuff = name.length() + EXTRA_BYTES_NAME_IS;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = NAME_IS;
	(getBuff())[COUNT_POSS] = sizeBuff - EXTRA_BYTES_NAME_IS;
	std::memcpy((getBuff() + EXTRA_BYTES_NAME_IS), name.c_str(), name.length());
	
	
}

nameIs::~nameIs()
{
	delete [] getBuff();

}

mapIs::mapIs(std::string mapName, unsigned char checksum)
{
	this->mapName = mapName;
	this->checksum = checksum;
	type = MAP_IS;
	this->sizeBuff = mapName.length() + EXTRA_BYTES_MAP_IS;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = MAP_IS;
	(getBuff())[COUNT_POSS] = mapName.length();
	(getBuff())[sizeBuff - 1] = checksum;
	std::memcpy((getBuff() + 2), mapName.c_str(), mapName.length());
}

mapIs::~mapIs()
{
	delete [] getBuff();
}

move::move(unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination)
{
	origin.row = rowOrigin;
	origin.col = columnOrigin;
	destination.row = rowDestination;
	destination.col = columnDestination;
	type = MOVE;
	sizeBuff = SIZE_MOVE_PACKAGE;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = MOVE;
	(getBuff())[FILA_OR_POS] = origin.row;
	(getBuff())[FILA_DES_POS] = destination.row;
	(getBuff())[COL_OR_POS] = origin.col+ MIN_COL;
	(getBuff())[COL_DES_POS] = destination.col+ MIN_COL;

}

move::move(Point origin, Point destination)
{
	this->origin = origin;
	this->destination = destination;
	type = MOVE;
	sizeBuff = SIZE_MOVE_PACKAGE;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = MOVE;
	(getBuff())[FILA_OR_POS] = origin.row;
	(getBuff())[FILA_DES_POS] = destination.row;
	(getBuff())[COL_OR_POS] = origin.col+ MIN_COL;
	(getBuff())[COL_DES_POS] = destination.col + MIN_COL;
}

move::~move()
{
	delete[] getBuff();
}

attack::attack(unsigned char dice, unsigned char rowOrigin, unsigned char columnOrigin, unsigned char rowDestination, unsigned char columnDestination)
{
	origin.row = rowOrigin;
	origin.col = columnOrigin;
	destination.row = rowDestination;
	destination.col = columnDestination;
	this->dice = dice;
	type = ATTACK;
	sizeBuff = SIZE_ATTACK_PACKAGE;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = ATTACK;
	(getBuff())[FILA_OR_POS] = origin.row;
	(getBuff())[FILA_DES_POS] = destination.row;
	(getBuff())[COL_OR_POS] = origin.col + MIN_COL;
	(getBuff())[COL_DES_POS] = destination.col + MIN_COL;
	(getBuff())[sizeBuff - 1] = dice;


}

attack::attack(unsigned char dice, Point origin, Point destination)
{
	this->origin = origin;
	this->destination = destination;
	this->dice = dice;
	type = ATTACK;

	sizeBuff = SIZE_ATTACK_PACKAGE;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = ATTACK;
	(getBuff())[FILA_OR_POS] = origin.row;
	(getBuff())[FILA_DES_POS] = destination.row;
	(getBuff())[COL_OR_POS] = origin.col + MIN_COL;
	(getBuff())[COL_DES_POS] = destination.col + MIN_COL;
	(getBuff())[sizeBuff - 1] = dice;
}

attack::~attack()
{
	delete [] getBuff();
}

ack::ack()
{
	type = ACK;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;

}

ack::~ack()
{
	delete getBuff();
}

name::name()
{
	type = NAME;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

name::~name()
{
	delete getBuff();
}

youStart::youStart()
{
	type = YOU_START;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

youStart::~youStart()
{
	delete getBuff();
}

iStart::iStart()
{
	type = I_START;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;

}

iStart::~iStart()
{
	delete getBuff();
}

pass::pass()
{
	type = PASS;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

pass::~pass()
{
	delete getBuff();
}

youWon::youWon()
{
	type = YOU_WON;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

youWon::~youWon()
{
	delete getBuff();
}

playAgain::playAgain()
{
	type = PLAY_AGAIN;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

playAgain::~playAgain()
{
	delete getBuff();
}

gameOver::gameOver()
{
	type = GAME_OVER;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

gameOver::~gameOver()
{
	delete getBuff();
}

error::error()
{
	type = ERROR;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

error::~error()
{
	delete getBuff();
}

quit::quit()
{
	type = QUIT;
	this->sizeBuff = 1;
	setBuff(new char);
	(getBuff())[PACKAGE_TYPE_POSS] = type;
}

quit::~quit()
{
	delete getBuff();
}

purchase::purchase(std::string ejercitoID, unsigned char row, unsigned char column)
{
	this->ejercitoID = ejercitoID;
	this->possition.row = row;
	this->possition.col= column;
	this->type = PURCHASE;

	sizeBuff = SIZE_PURCHASE_PACKAGE;
	setBuff(new char[sizeBuff]);
	(getBuff())[PACKAGE_TYPE_POSS] = PURCHASE;
	(getBuff())[FILA_POSS_PURCHASE] = row;
	(getBuff())[COL_POSS_PURCHASE] = column + MIN_COL;
	(getBuff())[1] = ejercitoID.c_str()[0];
	(getBuff())[2] = ejercitoID.c_str()[1];
	


}

purchase::purchase(std::string ejercitoID, Point possition)
{
	this->ejercitoID = ejercitoID;
	this->possition = possition;
	this->type = PURCHASE;
}

purchase::~purchase()
{
	delete[] getBuff();
}
