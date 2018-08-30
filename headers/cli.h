#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include "../headers/data_file.h"
#include "../headers/structs.h"

using namespace std;


class Cli
{
public:
    Cli();
    void checkCommand(string command);
    void loop();
    bool isReserved(string word);
    void createDB(string,int, int );
    data_file file;
    vector<string> reserved;
};


#endif