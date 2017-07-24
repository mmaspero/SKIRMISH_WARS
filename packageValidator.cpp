#include "packageValidator.h"
#include "packages.h"
#include <iostream>
#include <ctype.h>
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
	if (data == NULL || size == 0)
		return false;
	if ((data[0] == NAME_IS) && (data[1] > 0) && (data[1] + 2) == size)//??? magic number?? usare defines????
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