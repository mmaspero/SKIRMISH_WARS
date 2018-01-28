#include "Csv.h"
#include <cstring>

Csv::Csv(const char * fileName, char const * token) : f(fileName), tok(token)
{
	rows = cols = 0;

	if (f.good()) {
		bool valid = true;
		char buffer[CSV_MAX_LINE];
		char * aux;		//para recorrer el string
		std::string lastCol; //para ver si el ultimo separador estaba antes o despues de la ultima col
		memset(buffer, 0, sizeof(buffer));

		f.getline(buffer, sizeof(buffer));
		aux = strtok(buffer, tok);

		while (aux != NULL) {
			lastCol = std::string(aux);
			cols++;
			aux = strtok(NULL, tok);
		} //hay tantas columnas como tokens encuentre

		if (cols) { //siempre me va a dar uno mas!
			//n tokens separan n+1 substrings, que es lo que realmente conte
			//la unica excepcion es si no habia ningun token, en cuyo caso esta en 0
			//PERO POR AHORA LO DEJO ASI PORQUE ES MAS COMODO PARA CONTAR LAS COLUMNAS!
			rows++; //ya procese la primera linea
			if (lastCol.find_first_not_of(' ') != std::string::npos) {
				cols++;
			}


			while (valid == true && !f.eof()) {
				memset(buffer, 0, sizeof(buffer));
				f.getline(buffer, sizeof(buffer));

				if (buffer[0] != '\0') {
					rows++; //si no es valida lo veo despues y pongo todo en cero
					aux = strtok(buffer, tok);
					unsigned int colCount = cols;

					while (aux != NULL && colCount != 0) {
						lastCol = aux;
						colCount--;
						aux = strtok(NULL, tok);
					}
					if (lastCol.find_first_not_of(' ') != std::string::npos) {
						colCount--;
					}
					//si no llego a las dos condiciones al mismo tiempo, tengo columnas de mas o de menos
					if (aux != NULL || colCount != 0) {
						valid = false;
					}
				}
				else {
					if (!f.eof()) {
						valid = false; //si la fila esta vacia tiene que ser el final del archivo
					}
				}
			}
		}

		if (!valid || cols == 0) {
			cols = 0;
			rows = 0;
		}
		else {
			cols--; //ahora si, realmente tengo una columna menos de las que conte
		}
	}
}

Csv::~Csv()
{
	if (f.good()) {
		f.close();
	}
}

unsigned int Csv::getRows()
{
	return rows;
}

unsigned int Csv::getColumns()
{
	return cols;
}


std::string Csv::getCell(unsigned int row, unsigned int column)
{
	std::string cell;

	if (row < rows && column < cols) {
		char buffer[CSV_MAX_LINE];
		char * aux;
		memset(buffer, 0, sizeof(buffer));
	
		f.clear();					//por si habia llegado a eof
		f.seekg(0, std::ios::beg);	//voy al principio 

		do {
			f.getline(buffer, sizeof(buffer));
		} while (row--);
		aux = strtok(buffer, tok);

		while (column--) {
			aux = strtok(NULL, tok);
		}
		cell = std::string(aux);
	}

	return cell;
}

