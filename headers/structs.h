#include <iostream>


//tamano de 44 bytes
struct DB
{
    char nombre[30];
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