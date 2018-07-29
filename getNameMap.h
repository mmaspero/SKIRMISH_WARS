#pragma once
#include <string>
#include "Controller\network\network.h"

#define MAPS_PATH "Maps/"
#define CONNECTION_TIMEOUT 150 //2 minutos y medio (en segundos)

bool getClientInfo(network& n, std::string myName, std::string& clientName,
					std::string& mapPath, bool& first);

bool getServerInfo(network& n, std::string myName, std::string& serverName,
					std::string& mapPath, bool& first);