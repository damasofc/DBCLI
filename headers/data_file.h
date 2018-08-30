#ifndef DATA_FILE_H
#define DATA_FILE_H



#include <iostream>
#include <fstream>

class data_file
{
private:
	std::fstream *file;
	char *path;
public:
	data_file();
	data_file(char *path);
	~data_file();
	bool open();
	void close();
	void write(char *, unsigned int, unsigned int);
	char *read(unsigned int, unsigned int);
    bool exists(char *file);
};

#endif // DATA_FILE_H