#include "packageMaker.h"
#include "packageValidator.h"
#include <iostream>
void main(void)
{
	

}

/*genericPackage * test = NULL;
char tst1[7] = { 0x11,0x05,'A','R','I','E','L' };
test = packageMaker(tst1, 7);
if (test->getType() == NAME_IS)
{
std::string ts = ((nameIs *)test)->getName();
std::cout << ts.c_str() << std::endl;
}*/

/*char tst1[7] = { 0x11,0x05,'A','R','I','E','L' };
std::cout << nameIsValidator(tst1, 7) << std::endl;*/

//char tst1[8] = { 0x12,0x05,'A','R','I','E','L',12 };
//std::cout << mapIsValidator(tst1, 8) << std::endl;//1	
//std::cout << mapIsValidator(tst1, 7) << std::endl;//0
//std::cout << mapIsValidator(tst1, 9) << std::endl;//0
//tst1[2] = 0;
//std::cout << mapIsValidator(tst1, 8) << std::endl;//0 xq hay un caracter no imprimible en el nombre
//tst1[1] = 20;
//std::cout << mapIsValidator(tst1, 8) << std::endl;//cero xq el count no coincide con el tamaño del paquete