#include "../headers/structs.h"

DB getBDMetaData(char* name)
{
    std::string pathf = "databases/";
    pathf += name;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    data_file file(path);
    DB temp;
    if(file.open())
    {
        memcpy(temp.nombre,file.read(0,sizeof(temp.nombre)),sizeof(temp.nombre));
        memcpy(&temp.size,file.read(32,sizeof(int)),sizeof(int));
        memcpy(&temp.bitMPSize,file.read(36,sizeof(int)),sizeof(int));
        memcpy(&temp.cantBloques,file.read(40,sizeof(int)),sizeof(int));
        memcpy(&temp.firstTable,file.read(44,sizeof(int)),sizeof(int));
    }
    return temp;
};