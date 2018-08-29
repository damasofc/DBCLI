#include "../headers/cli.h"

#ifndef CLI
#define CLI

Cli::Cli()
{
    this->reserved = {"CREATE","DATABASE","DROP","TABLE","INSERT","INTO","VALUES","DELETE","FROM","WHERE",
    "SET","UPDATE","SELECT"};
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
    for(int i = 0; i < myString.size(); i++)
    {
        cout<<myString[i]<<endl;
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
#endif //CLI