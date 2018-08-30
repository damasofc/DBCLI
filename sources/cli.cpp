#include "../headers/cli.h"

using namespace std;
Cli::Cli()
{
    this->reserved = {"CREATE","DATABASE","DROP","TABLE","INSERT","INTO","VALUES","DELETE","FROM","WHERE",
    "SET","UPDATE","SELECT","SHOW","USE"};
}

void Cli::checkCommand(string command)
{
    vector<string> myString;
    istringstream ss(command);
    string token;
    while(getline(ss,token,' '))
    {
        myString.push_back(token);
    }
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

        }
        else
        {

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
    int sizeForDataBlocks = sizeBytes - 48 - 720 - 4000;
    int cantBloqs = (sizeForDataBlocks/dataBlockSize)-1;
    int bmpSize = cantBloqs/8;
    nuevo.size = size;
    nuevo.bitMPSize = bmpSize;
    nuevo.cantBloques = cantBloqs;
    nuevo.firstTable = -1;
    string pathf = "databases/";
    pathf += name;
    pathf += ".db";
    char path[pathf.length()];
    strcpy(path,pathf.c_str());
    this->file = data_file(path);
    this->file.open();
    this->file.write(reinterpret_cast<char *>(&nuevo),0,sizeof(nuevo));
    if(this->file.exists(path))
        cout<<"\t\tDATABASE "<<name<< " CREATED"<<endl;
    else
        cout<<"\t\tError: DATABASE wasn't created"<<endl;
    this->file.close();
}