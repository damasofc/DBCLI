
#ifndef STRUCTS_H
#define STRUCTS_H




#include <iostream>
#include <string.h>
#include "data_file.h"


//tamano de 48 bytes
struct DB
{
    char nombre[30];
    //este tamano del bitmap es en bytes
    int size;
    int bitMPSize;
    int cantBloques;
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
int charToInt(char* x);

#endif // STRUCTS_H