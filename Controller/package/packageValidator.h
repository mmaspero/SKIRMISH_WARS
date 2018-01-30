#pragma once
//oneBytePackageValidator
//accion: valida paquetes de datos de un byte (solo encabezado)
//recive: "data" paquete de datos, "size" tamaño del paquete, "key" encabezado del paquete
//devuelve: true si es valido, de lo contrario false
bool oneBytePackageValidator(char * data, unsigned int size, unsigned char key);

//nameIsValidator
//accion: valida paquetes de tipo NAME_IS
//recive: "data" paquete de datos, "size" tamaño del paquete
//devuelve: true si es valido, de lo contrario false
bool nameIsValidator(char * data, unsigned int size);

//mapIsValidator
//accion: valida paquetes de tipo MAP_IS
//recive: "data" paquete de datos, "size" tamaño del paquete
//devuelve: true si es valido, de lo contrario false
bool mapIsValidator(char * data, unsigned int size);

//moveValidator
//accion: valida paquetes de tipo MOVE
//recive: "data" paquete de datos, "size" tamaño del paquete
//devuelve: true si es valido, de lo contrario false
bool moveValidator(char * data, unsigned int size);

//attackValidator
//accion: valida paquetes de tipo ATTACK
//recive: "data" paquete de datos, "size" tamaño del paquete
//devuelve: true si es valido, de lo contrario false
bool attackValidator(char * data, unsigned int size);

//attackValidator
//accion: valida paquetes de tipo PURCHASE
//recive: "data" paquete de datos, "size" tamaño del paquete
//devuelve: true si es valido, de lo contrario false
bool purchaseValidator(char * data, unsigned int size);