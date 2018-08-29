#include "../headers/cli.h"

#ifndef CLI
#define CLI

Cli::Cli()
{

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
#endif //CLI