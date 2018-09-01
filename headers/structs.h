
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
    int firstTable = -1;
};

//tamano de 52 bytes
struct Tabla
{
    bool deleted;
    char nombre[30];
    int tamRegistro;
    int sigTabla;
    int dataBlockColumns;
    int firstColumn = -1;
    int firstRegistr = -1;
};

//tamano de 40 bytes
struct Columna
{
    char nombre[30];
    //tipo puede ser: I,D o, C
    char tipo;
    int size = -1;
    int sigColumna = -1;
};

DB getBDMetaData(char* name);
Tabla getTable(std::string name, std::string db);
Tabla getTable(int pos, std::string db);
Columna getColumna(int pos,Tabla tabla, std::string db);

#endif // STRUCTS_H