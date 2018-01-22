#include "Csv.h"
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS

Csv::Csv(const char * fileName, const char token) : f(fileName), tok(token)
{
	rows = cols = 0;

	if (f.good()) {
		bool valid = true;
		char buffer[CSV_MAX_LINE];
		char * aux;
		memset(buffer, 0, sizeof(buffer));

		f.getline(buffer, sizeof(buffer));
		aux = strchr(buffer, tok);

		while (aux != NULL) {
			cols++;
			aux = strchr(aux+1, tok);
		} //hay tantas columnas como tokens encuentre

		if (cols) {
			rows++; //ya procese la primera linea

			while (valid == true && !f.eof()) {
				memset(buffer, 0, sizeof(buffer));
				f.getline(buffer, sizeof(buffer));

				if (buffer[0] != '\0') {
					rows++; //si no es valida lo veo despues y pongo todo en cero
					aux = strchr(buffer, tok);
					unsigned int colCount = cols;

					while (aux != NULL && colCount != 0) {
						//					for (unsigned int i = 1; i < cols && aux != NULL; i++) {
											//empiez
						colCount--;
						aux = strchr(aux + 1, tok);
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
		char tokens[2] = { tok, '\0' }; //para respetar el formato que me pide strtok()
		memset(buffer, 0, sizeof(buffer));
	
		f.clear();					//por si habia llegado a eof
		f.seekg(0, std::ios::beg);	//voy al principio 

		do {
			f.getline(buffer, sizeof(buffer));
		} while (row--);
		aux = strtok(buffer, tokens);

		while (column--) {
			aux = strtok(NULL, tokens);
		}
		cell = std::string(aux);
	}

	return cell;
}

