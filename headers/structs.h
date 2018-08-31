
#ifndef STRUCTS_H
#define STRUCTS_H




#include <iostream>
#include <string.h>
#include "data_file.h"


//tamano de 52 bytes
struct DB
{
    char nombre[30];
    int size;
    //este tamano del bitmap es en bytes
    int bitMPSize;
    int cantBloques;
    int blockSize;
    int firstTable;
};

//tamano de 48 bytes
struct Tabla
{
    char nombre[30];
    int tamRegistro;
    int sigTabla;
    int firstColumn;
    int firstRegistr;
};

//tamano de 40 bytes
struct Columna
{
    char nombre[30];
    //tipo puede ser: I,D o, C
    char tipo;
    int size;
    int sigColumna;
};

DB getBDMetaData(char* name);
Tabla getTable(std::string name);
Tabla getTable(int pos);

#endif // STRUCTS_H