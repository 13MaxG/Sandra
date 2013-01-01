#include <iostream>
#include <fstream>
#include <ctime>

#include "system.h"
#include "lissajous.h"
#include "mandelbrot.h"
#include "buddhabrot.h"
#include "image.h"



using namespace std;

int main( int argc, char* argv[] )
{
    srand(time(0));

    cout<<"### ### ###"<<endl;
    cout<<"## SANDRA 1.0 ##"<<endl;
    cout<<"# Andrzej (Wem) Golonka, 2012"<<endl;
    cout<<"# http://WiecznyWem.tk"<<endl;
    cout<<"### ### ###"<<endl;
    cout<<endl;

    System *system = new System();


    char* config = "config.txt";

    if(argc >=2) config = argv[1];

    cout<<"Plik konfiguracyjny: "<<config<<endl;
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
    if(name == "#Mandelbrot")
    {
        system = new Mandelbrot();
    } else
    if(name == "#Buddhabrot")
    {
        system = new Buddhabrot();
    } else
    {
        ok  = false;
        cout<<"Nieznana animacja"<<endl;
    }

    if(ok)
    {
        cout<<"Animacja: "<<name<<endl;
        system->Load(config);
        system->Render();
    }

    return 0;
}

