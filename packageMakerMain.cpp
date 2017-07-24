#include "packageMaker.h"
#include "packageValidator.h"
#include <iostream>
void main(void)
{
	char tst1[7] = { 0x11,0x05,'A','R','I','E','L' };
	std::cout << nameIsValidator(tst1, 7) << std::endl;

}