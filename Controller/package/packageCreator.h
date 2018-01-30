#pragma once
#include "packages.h"

//todas las funciciones creatro no validan el los datos,
//se deven utilizar en conjunto con packageValidator
//
//

nameIs * nameIsCreator(char * data, unsigned int size);
mapIs * mapIsCreator(char * data, unsigned int size);
move * moveCreator(char * data, unsigned int size);
attack * attackCreator(char * data, unsigned int size);
