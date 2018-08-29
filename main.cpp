#include <iostream>
#include "./headers/data_file.h"
#include <sstream>
#include <vector>
#include "./headers/structs.h"
#include "./headers/cli.h"
using namespace std;
int main()
{
    Cli cli = Cli();
    cli.loop();
    
    return 0;
}
