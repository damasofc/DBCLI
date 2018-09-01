#include "../headers/cli.h"

using namespace std;
Cli::Cli()
{
    this->reserved = {"CREATE","DATABASE","DATABASES","DROP","TABLE","INSERT","INTO","VALUES","DELETE","FROM","WHERE",
    "SET","UPDATE","SELECT","SHOW","USE"};

    this->symbols = {"(",")",",",";"};
}

void Cli::checkCommand(string command)
{
    boost::to_upper(command);
    vector<string> myString;
    boost::split(myString,command,boost::is_any_of(" "));
    if(myString[0] == "CREATE")
    {
        if(myString[1] == "DATABASE")
        {
            string dbName = myString[2];
            int sizeDb = stoi(myString[3]);
            int dataBSize = stoi(myString[4]);
            this->createDB(dbName,sizeDb,dataBSize);
        }
        else if(myString[1] == "TABLE")
        {
            string tableName = myString[2];
            vector< pair<string, string> > campos;
            if(tableName.find('(') != string::npos)
            {
                tableName = tableName.substr(0,tableName.find('('));
                int a = 3;
                int iterator = 0;
                while(myString[a].find(')') == string::npos)
                {
                    string nombreCampo = myString[a];
                    string tipo;
                    a++;
                    if(myString[a].find(')') != string::npos)
                    {
                        tipo = myString[a].substr(0,myString[a].find(')'));
                        if(myString[a].find(')') != string::npos && myString[a].find(',') != string::npos )
                        {
                            tipo = myString[a].substr(0,myString[a].find(')')+1);
                            campos.emplace_back(nombreCampo,tipo);
                        }
                        else
                        {
                            tipo = myString[a].substr(0,myString[a].find(')'));
                            campos.emplace_back(nombreCampo,tipo);
                            break;
                        }
                    }
                    else
                    {
                        tipo = myString[a].substr(0,myString[a].find(','));
                        campos.emplace_back(nombreCampo,tipo);
                    }
                    iterator++;
                    a++;
                }
            }
            else
            {
                int a = 4;
                int iterator = 0;
                while(myString[a].find(')') == string::npos)
                {
                    string nombreCampo = myString[a];
                    string tipo;
                    a++;
                    if(myString[a].find(')') != string::npos)
                    {
                        tipo = myString[a].substr(0,myString[a].find(')'));
                        if(myString[a].find(')') != string::npos && myString[a].find(',') != string::npos )
                        {
                            tipo = myString[a].substr(0,myString[a].find(')')+1);
                            campos.emplace_back(nombreCampo,tipo);
                        }
                        else
                        {
                            tipo = myString[a].substr(0,myString[a].find(')'));
                            campos.emplace_back(nombreCampo,tipo);
                            break;
                        }
                    }
                    else
                    {
                        tipo = myString[a].substr(0,myString[a].find(','));
                        campos.emplace_back(nombreCampo,tipo);
                    }
                    iterator++;
                    a++;
                }
            }
            
            this->createTable(tableName,campos);
            
        }
        else
        {
            cout<<"\t\t***ERROR*** That command isn't recognized"<<endl;
        }
    }
    else if(myString[0] == "SHOW")
    {
        if(myString[1] == "DATABASE")
        {
            string nameBD = myString[2];
            this->showDB(nameBD);
        }
        else if(myString[1] == "DATABASES")
        {

        }
        else if(myString[1] == "TABLE")
        {
            if(databaseName.length() > 0)
            {
                this->showTable(myString[2]);
            }
            else
            {
                cout<<"***Error** Your haven't selected any Database"<<endl;
            }
        }
    }
    else if(myString[0] == "DROP")
    {
        if(myString[1] == "DATABASE")
        {
            string dbName = myString[2];
            this->deleteDB(dbName);
        }
        else if(myString[1] == "TABLE")
        {

        }
        else
        {

        }
    }
    else if(myString[0] == "USE")
    {
        if(myString[1] == "DATABASE")
        {
            string pathf = "databases/";
            pathf += myString[2];
            pathf += ".db";
            char path[pathf.length()];
            strcpy(path,pathf.c_str());
            if(this->file.exists(path))
            {
                this->databaseName = myString[2];
                this->file = data_file(path);
            }
            else
            {
                cout<<"***Error** That Database doesn't exists"<<endl;
            }
        }
    }
}

void Cli::loop()
{
    while(true)
    {
        string command;
        cout<< "DBCLI>>";
        getline(cin,command);
        this->checkCommand(command);
    }
}

bool Cli::isReserved(string word)
{
    //ESTE 13 ES LA CANTIDAD DE PALABRAS RESERVADAS
    for(int i = 0; i < reserved.size(); i++)
    {
        if(word == reserved[i])
            return true;
    }
    return false;
    
}
void Cli::createDB(string name, int size, int dataBlockSize)
{
    DB nuevo;
    memcpy(nuevo.nombre,name.c_str(),name.length());
    int sizeBytes = size * 1000000;
    int sizeForDataBlocks = sizeBytes - 52 - dataBlockSize;
    int cantBloqs = (sizeForDataBlocks/dataBlockSize);
    int bmpSize = cantBloqs/8;
    nuevo.size = size;
    nuevo.bitMPSize = bmpSize;
    nuevo.cantBloques = cantBloqs;
    nuevo.blockSize = dataBlockSize;
    nuevo.firstTable = -1;
    string pathf = "databases/";
    pathf += name;
    pathf += ".db";
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    this->file = data_file(path);
    this->file.open();
    //escribo el struct de la metadata de la BD
    this->file.write(reinterpret_cast<char *>(&nuevo),0,sizeof(nuevo));
    //llenar con 0 todos las posiciones del bitmap
    int i = 0;
    char index = '0';
    while(i < bmpSize) 
    {
        this->file.write(&index,(sizeof(nuevo)+i),1);
        i++;
    }
    if(this->file.exists(path))
        cout<<"\t\tDATABASE "<<name<< " CREATED"<<endl;
    else
        cout<<"\t\tError: DATABASE wasn't created"<<endl;
    this->file.close();
}

void Cli::showDB(string name)
{
    name += ".db";
    string pathf = "databases/";
    pathf += name;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    if(!this->file.exists(path))
    {
        cout<<"\t\t\tDatabase "<<name<<" doesn't exists"<<endl;
        return;
    }

    DB baseDatos = getBDMetaData(path);
    
    cout<<"\t\t\tDatabase: "<<baseDatos.nombre<<endl;
    cout<<"\t\t"<<"Size: "<<"\t\t"<<baseDatos.size<<"MB"<<"  |  "<<baseDatos.size*1000000<<"B"<<endl;
    cout<<"\t\t"<<"BitmapSize: "<<"\t\t"<<baseDatos.bitMPSize<<"B"<<endl;
    cout<<"\t\t"<<"BlockSize: "<<"\t\t"<<baseDatos.blockSize<<endl;
    cout<<"\t\t"<<"CantBloques: "<<"\t\t"<<baseDatos.cantBloques<<endl;
    cout<<"\t\t"<<"FirsTable: "<<"\t\t"<<baseDatos.firstTable<<endl;
}

void Cli::showTable(string name)
{
    Tabla t = getTable(name,databaseName);
    if(t.tamRegistro < 0)
    {
        cout<<"\t\t***Error*** That Table doesn't exists"<<endl;
    }
    else
    {
        cout<<"\t\t\tTable: "<<t.nombre<<endl;
        cout<<"\t\t"<<"SizeReg: "<<"\t\t"<<t.tamRegistro<<endl;
        cout<<"\t\t"<<"NextTable: "<<"\t\t"<<t.sigTabla<<endl;
        cout<<"\t\t"<<"DataBlockCols: "<<"\t\t"<<t.dataBlockColumns<<endl;
        cout<<"\t\t"<<"FirstCol: "<<"\t\t"<<t.firstColumn<<endl;
        cout<<"\t\t"<<"FirstRegister: "<<"\t\t"<<t.firstRegistr<<endl;
    }
}
void Cli::deleteDB(string name)
{
    name += ".db";
    string pathf = "databases/";
    pathf += name;
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    if(!this->file.exists(path))
    {
        cout<<"\t\t\tDatabase "<<name<<" doesn't exists"<<endl;
        return;
    }
    if(remove(path) == 0)
    {
        cout<<"\t\t\tDatabase: "<<name<<" has been deleted"<<endl;
    }
    else
    {
        cout<<"\t\t\tDatabase: "<<name<<" hasn't been deleted"<<endl;
    }
}

void Cli::createTable(string name,vector<pair<string,string> > campos )
{
    if(databaseName.length() > 0)
    {
        string nombrBD = databaseName + ".db";
        string pathf = "databases/";
        pathf += nombrBD;
        char path[pathf.length()];
        strcpy(path,pathf.c_str());
        DB baseDatos = getBDMetaData(path);
        if(baseDatos.firstTable == -1)
        {
            int posTable = sizeof(baseDatos) + baseDatos.bitMPSize;
            Tabla tabla;
            tabla.deleted = false;
            memcpy(tabla.nombre,name.c_str(),name.length());
            tabla.tamRegistro = this->getSizeRegister(campos);
            tabla.sigTabla = -1;
            tabla.dataBlockColumns = 2;
            tabla.firstColumn = 0;
            this->file = data_file(path);
            if(this->file.open())
            {
                int posInicioTabla = sizeof(DB) + baseDatos.bitMPSize;
                this->file.write(reinterpret_cast<char *>(&tabla),posInicioTabla,sizeof(tabla));
                cout<<"\t\tTable "<<name<<" has been created"<<endl;
                baseDatos.firstTable = 0;
                this->file.write(reinterpret_cast<char*>(&baseDatos),0,sizeof(baseDatos));
                //guardar las columnas:
                for(int i = 0; i < campos.size(); i++)
                {
                    string namecol = campos[i].first;
                    string type = campos[i].second;
                    if(type == "INT")
                        this->createColumn(namecol,type,4,baseDatos,tabla);
                    else if(type == "DOUBLE")
                        this->createColumn(namecol,type,8,baseDatos,tabla);
                    else
                    {
                        vector<string> strs;
                        boost::split(strs,type,boost::is_any_of("("));
                        boost::split(strs,strs[1],boost::is_any_of(")"));
                        int sizeCol = stoi(strs[0]);
                        this->createColumn(namecol,"CHAR",sizeCol,baseDatos,tabla);
                    }
                }
                this->file.close();
            }
            else
            {
                cout<<"\t\tError"<<endl;
            }


        }
    }
    else
    {
        cout<<"***Error** Your haven't selected any Database"<<endl;
    }
}

//FALTA EL CREATE COLUMN
void Cli::createColumn(string name, string type, int size,DB base,Tabla tabla)
{
    Columna col;
    memcpy(col.nombre,name.c_str(),name.length());
    // switch(type)
    // {
    //     case "INT":
    //         col.tipo = 'I';
    //     break;
    //     case "CHAR":
    //         col.tipo = 'C';
    //     break;
    //     case "DOUBLE":
    //         col.tipo = 'D';
    //     break;
    //     default:

    //     break;
    // }
    // col.size = size;
}

int Cli::getSizeRegister(vector<pair<string,string> > campos)
{
    int size = 0;
    for(int i = 0; i < campos.size(); i++)
    {
        string type = campos[i].second;
        if(type == "INT")
            size += 4;
        else if(type == "DOUBLE")
            size += 8;
        else
        {
            vector<string> strs;
            boost::split(strs,type,boost::is_any_of("("));
            boost::split(strs,strs[1],boost::is_any_of(")"));
            size += stoi(strs[0]);
        }
    }
    return size;
}