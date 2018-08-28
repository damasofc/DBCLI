#include "../headers/data_file.h"

using namespace std;

data_file::data_file(char* direccion)
{
    this->direccion = new  char[sizeof(direccion)];
    this->archivo = new fstream();
    strcpy(this->direccion, direccion);
}

void data_file::abrir()
{
    this->archivo->open(this->direccion,fstream::out | fstream::app | ios::binary);
}

void data_file::cerrar()
{
    this->archivo->close();
}

void data_file::escribir(char *input,int pos,int bytes)
{
    ofstream out(this->direccion,ios::out | ios::in | ios::binary);
    out.seekp(pos);
    out.write(input,bytes);
}

char* data_file::leer(int posicion, int bytes)
{
    char* retorno = new char[bytes];
    ifstream in(this->direccion,ios::in | ios::binary);
    in.seekg(posicion);
    in.read(retorno,bytes);
    return retorno;
}

char* data_file::leer(int bytes)
{
    char* retorno = new char[bytes];
    ifstream in(this->direccion);
    in.read(retorno,bytes);
    return retorno;
}

void data_file::set_pos(int pos)
{
    this->archivo->seekg(pos);
}