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
        file.close();
    }
    return temp;
};

Columna getColumna(int pos,Tabla tabla, std::string db)
{
    std::string nombrBD = db + ".db";
    std::string pathf = "databases/";
    pathf += nombrBD;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    data_file file(path);
    if(file.open())
    {
        DB mdBase = getBDMetaData(path);
    }
}

Tabla getTable(int pos, std::string db)
{
    std::string nombrBD = db + ".db";
    std::string pathf = "databases/";
    pathf += nombrBD;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    data_file file(path);
    Tabla retorno;
    if(file.open())
    {
        DB mdBase = getBDMetaData(path);
        int posTabla = sizeof(DB) + mdBase.bitMPSize + (pos * sizeof(Tabla));
        memcpy(&retorno.deleted,file.read(posTabla,sizeof(retorno.deleted)),sizeof(retorno.deleted));
        posTabla += sizeof(retorno.deleted);
        memcpy(&retorno.nombre,file.read(posTabla,sizeof(retorno.nombre)),sizeof(retorno.nombre));
        posTabla += sizeof(retorno.nombre) + 1;
        memcpy(&retorno.tamRegistro,file.read(posTabla,sizeof(retorno.tamRegistro)),sizeof(retorno.tamRegistro));
        posTabla += sizeof(retorno.tamRegistro);
        memcpy(&retorno.sigTabla,file.read(posTabla,sizeof(retorno.sigTabla)),sizeof(retorno.sigTabla));
        posTabla += sizeof(retorno.sigTabla);
        memcpy(&retorno.dataBlockColumns,file.read(posTabla,sizeof(retorno.dataBlockColumns)),sizeof(retorno.dataBlockColumns));
        posTabla += sizeof(retorno.dataBlockColumns);
        memcpy(&retorno.firstColumn,file.read(posTabla,sizeof(retorno.firstColumn)),sizeof(retorno.firstColumn));
        posTabla += sizeof(retorno.firstColumn);
        memcpy(&retorno.firstRegistr,file.read(posTabla,sizeof(retorno.firstRegistr)),sizeof(retorno.firstRegistr));
        posTabla += sizeof(retorno.firstRegistr);
        file.close();
    }
    return retorno;
}

Tabla getTable(std::string name, std::string db)
{
    std::string nombrBD = db + ".db";
    std::string pathf = "databases/";
    pathf += nombrBD;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    data_file file(path);
    Tabla retorno;
    if(file.open())
    {
        DB mdBase = getBDMetaData(path);
        int posTabla = sizeof(DB) + mdBase.bitMPSize;
        if(mdBase.firstTable != -1)
        {
            int posIT = mdBase.firstTable;
            bool eof = file.isEOF(posTabla);
            while(!eof && posTabla < (sizeof(DB)+mdBase.bitMPSize + (2* mdBase.blockSize)))
            {
                Tabla temp = getTable(posIT,db);
                if(temp.nombre == name && !temp.deleted)
                    return temp;
                posIT++;
                posTabla += sizeof(Tabla);
                eof = file.isEOF(posTabla);
            }
        }
        file.close();
    }
    return retorno;
}