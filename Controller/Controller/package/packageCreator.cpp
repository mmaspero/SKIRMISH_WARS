#include "packageCreator.h"

nameIs * nameIsCreator(char * data, unsigned int size)
{
	return new nameIs(std::string(data + 2, data[COUNT_POSS]));
}

mapIs * mapIsCreator(char * data, unsigned int size)
{
	return new mapIs(std::string(data+2, data[COUNT_POSS]), data[size-1]);
}

move * moveCreator(char * data, unsigned int size)
{
	return new move(data[FILA_OR_POS], data[COL_OR_POS] - MIN_COL, data[FILA_DES_POS], data[COL_DES_POS] - MIN_COL);
}

attack * attackCreator(char * data, unsigned int size)
{
	return new attack(data[5],data[FILA_OR_POS], data[COL_OR_POS] - MIN_COL, data[FILA_DES_POS], data[COL_DES_POS] - MIN_COL);
}

