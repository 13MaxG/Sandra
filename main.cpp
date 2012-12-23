#include <iostream>
#include <fstream>

#include "system.h"
#include "lissajous.h"
#include "mandelbrot.h"

using namespace std;

int main( int argc, char* argv[] )
{
    cout<<"## SANDRA 1.0 ##"<<endl;
    cout<<"# Andrzej (Wem) Golonka, 2012"<<endl;
    cout<<"# http://WiecznyWem.tk"<<endl;

    System *system = new System();


    char* config = "config.txt";
    double info = 0.05;

    if(argc >=2) config = argv[1];
    if(argc >=3) info = fromString<double>(argv[2]) / 100.0;

    cout<<"Plik konfiguracyjny: "<<config<<endl;
    fstream file;
    string name;

    file.open(config, ios::in);
    file>>name;
    file.close();

    bool ok = true;

    if(name == "#Lissajous")
    {
      //  system = new Lissajous();
    } else
    if(name == "#Mandelbrot")
    {
        //system = new Mandelbrot();
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

