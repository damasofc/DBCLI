#include "../headers/structs.h"

DB getBDMetaData(char* name)
{
    data_file file(name);
    DB temp;
    if(file.open())
    {
        memcpy(temp.nombre,file.read(0,sizeof(temp.nombre)),sizeof(temp.nombre));
        memcpy(&temp.size,file.read(32,sizeof(int)),sizeof(int));
        memcpy(&temp.bitMPSize,file.read(36,sizeof(int)),sizeof(int));
        memcpy(&temp.cantBloques,file.read(40,sizeof(int)),sizeof(int));
        memcpy(&temp.blockSize,file.read(44,sizeof(int)),sizeof(int));
        memcpy(&temp.firstTable,file.read(48,sizeof(int)),sizeof(int));
    }
    return temp;
};