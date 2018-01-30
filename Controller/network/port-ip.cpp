#include "port-ip.h"
#include <string>




port::~port()
{
}

std::string port::getPortAsString()
{
	return std::to_string(portNumber);
}



ip::~ip()
{
}
