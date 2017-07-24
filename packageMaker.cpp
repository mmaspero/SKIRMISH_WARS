#include "packageMaker.h"

#include "packageValidator.h"

genericPackage * packageMaker(char * data, unsigned int size)
{
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
			//cosntruir el paquete
		}
		break;
	case MAP_IS:
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
		break;
	case PURCHASE:
		break;
	case ATTACK:
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



