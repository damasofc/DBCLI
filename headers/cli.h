#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include "../headers/data_file.h"
#include "../headers/structs.h"
#include <bitset>
#include <cstdio>
#include <boost/algorithm/string.hpp>

using namespace std;


class Cli
{
public:
    Cli();
    void checkCommand(string command);
    void loop();
    bool isReserved(string word);
    void createDB(string,int, int );
    void showDB(string name);
    void deleteDB(string name);
    void createTable(string name,vector<pair<string,string> > campos );
    void showTable(string name);
    void createColumn(string name,string type,int size, DB base, Tabla tabla);
    int getSizeRegister(vector<pair<string,string> > campos);
    data_file file;
    vector<string> reserved;
    vector<string> symbols;
    string databaseName;
};


#endif