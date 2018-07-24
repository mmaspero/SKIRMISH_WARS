#include "packageValidator.h"
#include "packages.h"
#include <iostream>
#include <ctype.h>
#include"../../Game model/types.h"

bool filValidator(unsigned char filNumb);
bool colValidator(unsigned char colNumb);
bool oneBytePackageValidator(char * data, unsigned int size, unsigned char key)
{
	if ((size == 1) && (data[0] == key))//el tamaño del paquete deve ser exactamente 1
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool nameIsValidator(char * data, unsigned int size)
{
	if (data == NULL || size == 0)//chequeo que halla informacion
		return false;
	if ((data[PACKAGE_TYPE_POSS] == NAME_IS) && (data[COUNT_POSS] > 0) && (data[COUNT_POSS] + EXTRA_BYTES_NAME_IS) == size)//??? magic number?? usare defines????
	{
		for (int i = 2; i < size; i++)//chequeo si son todos los caracteres imprimibles
		{
			if (isprint(data[i]) == 0)//encontre algun caracter que no sea imprimible
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool mapIsValidator(char * data, unsigned int size)
{
	if (data == NULL || size == 0)//chequeo que halla informacion
		return false;
	if ((data[PACKAGE_TYPE_POSS] == MAP_IS) && (data[COUNT_POSS] > 0) && (data[COUNT_POSS] + EXTRA_BYTES_MAP_IS) == size)
	{
		for (int i = 2; i < (size-1); i++)//chequeo si son todos los caracteres imprimibles, se verifica hasta el ante ultimo byte, puesto que el ultimo es el checksum
		{
			if (isprint(data[i]) == 0)//encontre algun caracter que no sea imprimible
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool moveValidator(char * data, unsigned int size)
{
	if (data != NULL && size == SIZE_MOVE_PACKAGE)
	{
		if (data[PACKAGE_TYPE_POSS] == MOVE && colValidator(data[COL_OR_POS]) && colValidator(data[COL_DES_POS]) && filValidator(data[FILA_OR_POS]) && filValidator(data[FILA_DES_POS]))
		{
			return true;
		}
	}
	return false;
}

bool attackValidator(char * data, unsigned int size)
{
	if (data != NULL && size == SIZE_ATTACK_PACKAGE)
	{
		if (data[PACKAGE_TYPE_POSS] == ATTACK && colValidator(data[COL_OR_POS]) && colValidator(data[COL_DES_POS]) && filValidator(data[FILA_OR_POS]) && filValidator(data[FILA_DES_POS]))
		{
			if((data[SIZE_ATTACK_PACKAGE-1]<=0X06)&&(data[SIZE_ATTACK_PACKAGE - 1] >= 0X01))//dado
			{
				return true;
			}
		}
	}
	return false;

}

bool purchaseValidator(char * data, unsigned int size)
{
	std::string idEjercitos[N_UNIT_TYPES] = {RE_STR,RO_STR,ME_STR,IN_STR,TA_STR,AR_STR,AA_STR,AP_STR,MT_STR};
	std::string tempId;

	if (size == SIZE_PURCHASE_PACKAGE)
	{
		tempId.push_back(data[1]);
		tempId.push_back(data[2]);
		if (colValidator(data[COL_POSS_PURCHASE]) && filValidator(data[FILA_POSS_PURCHASE]))
		{
			for (int i = 0; i < N_UNIT_TYPES; i++)
			{
				if (tempId == idEjercitos[i])
				{
					return true;
				}
			}
		}
	}
	return false;
	
}

bool colValidator(unsigned char colNumb)
{
	if ((colNumb >= MIN_COL) && (colNumb <= MAX_COL))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool filValidator(unsigned char filNumb)
{
	if ((filNumb >= MIN_FIL) && (filNumb <= MAX_FIL))
	{
		return true;
	}
	else
	{
		return false;
	}
}

