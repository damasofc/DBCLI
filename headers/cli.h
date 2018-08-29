#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Cli
{
public:
    Cli();
    void checkCommand(string command);
    void loop();
    bool isReserved(string word);
    vector<string> reserved;
};


#endif