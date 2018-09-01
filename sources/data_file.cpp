#include "../headers/data_file.h"

using namespace std;

data_file::data_file() {
	file = NULL;
	path = NULL;
}

data_file::data_file(char *path) {
	this->path = path;
	file = new fstream();
}


data_file::~data_file() 
{
	
}

bool data_file::open() {
	if (file == NULL) 
		return false;
	else {
		if (!exists(this->path)) {
			this->file->open(path, ios::in | ios::out | ios::binary | ios::trunc);
			if (!this->file->good()) {
				return false;
			}
		}
		else
		{
			this->file->open(path, fstream::in | fstream::out | fstream::binary);
			if (!this->file->good()) {
				return false;
			}
		}
		return true;
	}
}

void data_file::close() {
	if (this->file == NULL)
		cout << "No se puede cerrar el archivo" << endl;
	else {
		if(this->file->is_open())
			this->file->close();
		else 
			cout << "no se puede cerrar el archivo, nunca ha sido abierto" << endl;
	}
		
}

void data_file::write(char * data, unsigned int pos, unsigned int lenght) {
	this->file->seekp(pos, ios::beg);
	this->file->write((char*)data, lenght);
}

char * data_file::read(unsigned int pos, unsigned int size) {
	char *info = new char[size];
	this->file->seekg(pos);
	this->file->read((char*)info, size);
	return info;
}

bool data_file::exists(char *file)
{
    ifstream f(file);
    return f.good();
}
bool data_file::isEOF(int pos)
{
	this->file->seekg(0,ios::end);
	int fin = file->tellg();
	if(pos < fin)
		return false;
	return true;
}