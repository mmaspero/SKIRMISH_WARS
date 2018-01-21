#include "packageMaker.h"

#include "packageValidator.h"
#include "packageCreator.h"
genericPackage * packageMaker(char * data, unsigned int size)
{
	std::string tempId;
	if (data == NULL || size == 0)//chequeo si llego informacion
	{
		return NULL;
	}

	switch(data[0])//en la primera posicion del arreglo deveria estar el tipo de paquete, de esta manera se clasifica
	{			   //para su posterior analisis
	case ACK:
		if (oneBytePackageValidator(data, size, ACK))
		{
			return new ack;
		}
		else
		{
			return NULL;
		}
		break;
	case NAME:
		if (oneBytePackageValidator(data, size, NAME))
		{
			return new name;
		}
		else
		{
			return NULL;
		}
		break;
	case NAME_IS:
		if (nameIsValidator(data, size))
		{
			return nameIsCreator(data, size);
		}
		break;
	case MAP_IS:
		if(mapIsValidator(data,size))
		{
			return mapIsCreator(data,size);
		}
		else
		{
			return NULL;
		}
		break;
	case YOU_START:
		if (oneBytePackageValidator(data, size, YOU_START))
		{
			return new youStart;
		}
		else
		{
			return NULL;
		}
		break;
	case I_START:
		if (oneBytePackageValidator(data, size, I_START))
		{
			return new iStart;
		}
		else
		{
			return NULL;
		}
		break;
	case PASS:
		if (oneBytePackageValidator(data, size, PASS))
		{
			return new pass;
		}
		else
		{
			return NULL;
		}
		break;
	case MOVE:
		if(moveValidator(data,size))
		{
			return moveCreator(data,size);
		}
		else
		{
			return NULL;
		}
		break;
	case PURCHASE:
		tempId.push_back(data[1]);
		tempId.push_back(data[2]);
		if (purchaseValidator(data, size))
		{
			return new purchase(tempId, data[3], data[4]);
		}
		else
		{
			return NULL;
		}
		break;
	case ATTACK:
		if (attackValidator(data, size))
		{
			return attackCreator(data,size);
		}
		else
		{
			return NULL;
		}
		break;
	case YOU_WON:
		if (oneBytePackageValidator(data, size, YOU_WON))
		{

			return new youWon;
		}
		else
		{
			return NULL;
		}
		break;
	case PLAY_AGAIN:
		if (oneBytePackageValidator(data, size, PLAY_AGAIN))
		{
			return new playAgain;
		}
		else
		{
			return NULL;
		}
		break;
	case GAME_OVER:
		if (oneBytePackageValidator(data, size, GAME_OVER))
		{
			return new gameOver;
		}
		else
		{
			return NULL;
		}
		break;
	case ERROR:
		if (oneBytePackageValidator(data, size, ERROR))
		{
			return new error;
		}
		else
		{
			return NULL;
		}
		break;
	case QUIT:
		if (oneBytePackageValidator(data, size, QUIT))
		{
			return new quit;
		}
		else
		{
			return NULL;
		}
		break;
	default:
		return NULL;
		break;
	}
}



