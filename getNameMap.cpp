#include "getNameMap.h"

#include "Controller\package\packageValidator.h"
#include "Controller\package\packages.h"
#include "Controller\package\packageMaker.h"
#include "Controller\eventSource\timerEvSource.h"
#include "checksum.h"
#include "directory.h"
#include <vector>
#include <cstdlib>

genericPackage * waitForSpecificPackage(int type, unsigned int timeout, network& n);
genericPackage * waitForPackage(unsigned int timeout, network&n);

bool getClientInfo(network& n, std::string myName, std::string& clientName, std::string& mapPath, bool& first)
{
	bool valid = false;
	directory mapsDir(MAPS_PATH);
	nameIs serverName(myName);
	ack ackpckg;


	if (!mapsDir.isError() && nameIsValidator(serverName.getBuff(), serverName.getSizeBuff())) {
		std::vector<std::string> maps;
		std::string s = mapsDir.getNextPath("csv");
		while (!s.empty()) {
			mapIs temp(((boost::filesystem::path(s)).stem()).string(),0);
			if (mapIsValidator(temp.getBuff(),temp.getSizeBuff())) {
				maps.push_back(s); //solo considero mapas validos!
			}
			s = mapsDir.getNextPath("csv");
		}

		if (!maps.empty()) { //habia al menos un mapa valido en el path que me pasaron
			name askName;
			n.sendData(askName.getBuff(), askName.getSizeBuff()); //pregunto nombre

			genericPackage * pckg = waitForSpecificPackage(NAME_IS, CONNECTION_TIMEOUT, n);
			//espero que me manden el nombre del cliente
			if (pckg != nullptr) {
				clientName = ((nameIs*)pckg)->getName(); //guardo nombre
				delete pckg;

				n.sendData(ackpckg.getBuff(), ackpckg.getSizeBuff());
				//confirmo que recibi nombre
				pckg = waitForSpecificPackage(NAME, CONNECTION_TIMEOUT, n);
				// espero que me pregunten mi nombre
				if (pckg != nullptr) {
					delete pckg;
					n.sendData(serverName.getBuff(), serverName.getSizeBuff());
					//mando mi nombre
					pckg = waitForSpecificPackage(ACK, CONNECTION_TIMEOUT, n);
					//espero que me confirmen que llego mi nombre

					if (pckg != nullptr) {
						delete pckg;
						mapPath = maps[(rand() % maps.size())];//elijo un mapa cualquiera
						unsigned char mapSum;
						if (checksum(mapPath, mapSum)) {
							pckg = new mapIs (((boost::filesystem::path(mapPath)).stem()).string(), mapSum);
							n.sendData(pckg->getBuff(), pckg->getSizeBuff());//madno el mapa
							delete pckg;

							pckg = waitForSpecificPackage(ACK, CONNECTION_TIMEOUT, n);
							//espero que me confirmen que llego el mapa

							if (pckg != nullptr) {
								delete pckg;
								first = ((rand() % 2)==0);
								if (first) {
									pckg = new iStart;
									n.sendData(pckg->getBuff(), pckg->getSizeBuff());
									delete pckg;
									pckg = waitForSpecificPackage(ACK, CONNECTION_TIMEOUT, n);
									if (pckg != nullptr) {
										delete pckg;
										valid = true;
									}
								}
								else {
									pckg = new youStart;
									n.sendData(pckg->getBuff(), pckg->getSizeBuff());
									delete pckg;
									valid = true;
								}
							}
						}
					}
				}
			}
		}
	}
	return valid;
}

bool getServerInfo(network& n, std::string myName, std::string& serverName, std::string& mapPath, bool& first)
{
	bool valid = false;
	nameIs clientName(myName);
	ack ackpckg;
	genericPackage * pckg = nullptr;

	if (nameIsValidator(clientName.getBuff(), clientName.getSizeBuff())) {
		pckg = waitForSpecificPackage(NAME, CONNECTION_TIMEOUT, n);

		if (pckg != nullptr) {
			delete pckg;
			n.sendData(clientName.getBuff(), clientName.getSizeBuff());

			pckg = waitForSpecificPackage(ACK, CONNECTION_TIMEOUT, n);
			if (pckg != nullptr) {
				delete pckg;
				pckg = new name;
				n.sendData(pckg->getBuff(), pckg->getSizeBuff());
				delete pckg;
				
				pckg = waitForSpecificPackage(NAME_IS, CONNECTION_TIMEOUT, n);
				if (pckg != nullptr) {
					serverName = ((nameIs*)pckg)->getName();
					delete pckg;
					n.sendData(ackpckg.getBuff(), ackpckg.getSizeBuff());

					pckg = waitForSpecificPackage(MAP_IS, CONNECTION_TIMEOUT, n);
					if (pckg != nullptr) {
						mapPath = std::string(MAPS_PATH);
						mapPath.append(((mapIs*)pckg)->getMapName());
						mapPath.append(".csv");
						unsigned char mapSum;
						if (checksum(mapPath, mapSum) && mapSum == unsigned char(((mapIs*)pckg)->getChecksum())) {
							delete pckg;
							n.sendData(ackpckg.getBuff(), ackpckg.getSizeBuff());
							pckg = waitForPackage(CONNECTION_TIMEOUT, n);

							if (pckg != nullptr) {
								if (pckg->getType() == I_START) {
									first = false;
									n.sendData(ackpckg.getBuff(), ackpckg.getSizeBuff());
									valid = true;
								}
								else if (pckg->getType() == YOU_START) {
									first = true;
									valid = true;
								}
							}
						}
						delete pckg;
					}
				}
			}
		}
	}
	 
	return valid;
}

genericPackage * waitForSpecificPackage(int type, unsigned int timeout, network& n) {
	genericPackage * pckg = waitForPackage(timeout, n);
	if (pckg != nullptr && pckg->getType() != type) {
		delete pckg;
		pckg = nullptr;
	}
	return pckg;
}

genericPackage * waitForPackage(unsigned int timeout, network&n)
{
	timerEvSource timer(timeout);
	char buff[500];
	genericPackage * pckg = nullptr;

	int data = n.reciveData(buff, sizeof(buff));
	timer.startTimer();

	while (timer.getEvent() == NULL && data == MY_EMPTY) {
		data = n.reciveData(buff, sizeof(buff));
	}

	if (data != MY_ERROR && data != MY_EMPTY) {
		pckg = packageMaker(buff, data);
	}

	return pckg;
}