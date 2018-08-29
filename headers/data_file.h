#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <fstream>
#include <cstring>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

class data_file
{
public:
    data_file(char* direccion);
    void abrir();
    void cerrar();
    void escribir(char* input,int pos,int bytes);
    char* leer(int posicion, int bytes);
    char* leer(int bytes);
    void set_pos(int pos);

    char* direccion;
    fstream* archivo;
};


#endif