#pragma once
#include <iostream>
class port
{
public:
	
	port(unsigned int portNumber=0) { this->portNumber = portNumber; };
	~port();
	unsigned int getPortAsInt() { return portNumber; };
	std::string getPortAsString();
private:
	unsigned int portNumber;

};

class ip
{
public:
	
	ip(std::string ipNumber="0"){ this->ipNumber = ipNumber;};
	~ip();
	std::string getIp() { return ipNumber; };

private:
	std::string ipNumber;
	

};
