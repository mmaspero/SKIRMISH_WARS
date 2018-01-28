#pragma once
#include <fstream>
#include <string>
//lector de archivos .csv sin header

//	el archivo que se use debe tener todas las filas completas!! puede tener una celda vacia (dos separadores sin nada
//en el medio), pero todas las filas deben tener la misma cantidad de separadores 
//si no se puede abrir el archivo, getRows y getColumns van a devolver 0, y getCell un string vacio

#define CSV_MAX_LINE	500	 //maximo numero de caracteres por linea, incluyendo el '\n'

class Csv {
public:
	Csv(const char * fileName, const char * tokens = ";,");
	~Csv();

	unsigned int getRows();		
	unsigned int getColumns();
	std::string getCell(unsigned int row, unsigned int column);
	// row y column son zero-based: si row>=rows o column >=cols, devuelve string vacio

private:
	std::ifstream f;
	char const * tok;

	unsigned int rows;
	unsigned int cols;
};