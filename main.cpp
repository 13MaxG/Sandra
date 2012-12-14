#include <iostream>
#include <fstream>

#include "lissajous.h"


using namespace std;

int main()
{
    System *system;

    char* config = "config.txt";
    fstream file;
    string name;

    file.open(config, ios::in);
    file>>name;
    file.close();

    bool ok = true;

    if(name == "#Lissajous")
    {
        system = new Lissajous();
    } else
    {
        ok  = false;
        cout<<"Nieznana animacja"<<endl;
    }

    if(ok)
    {
        system->Load(config);
        system->Render();
    }

    return 0;
}

