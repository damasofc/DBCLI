#include "./headers/cli.h"
#include <bitset>
#include "../headers/data_file.h"
using namespace std;
int main()
{
    // Cli cli = Cli();
    // cli.loop();
    // bitset<256> foo(4);
    // foo[255] = 1;
    data_file file("prueba.dat");
    if(file.open())
    {
        // string s = foo.to_string();
        // file.write((char*)&s,0,s.length()/8);
        // file.close();
        char data[32];
        memcpy(data,file.read(0,32),32)
        bitset<256> foo(data);
        cout<<"abrio"<<endl;
        cout<<foo<<endl;
    }
    
    return 0;
}
