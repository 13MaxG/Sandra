#include <iostream>
#include <fstream>
#include <ctime>

#include "system.h"
#include "lissajous.h"
#include "mandelbrot.h"
#include "buddhabrot.h"
#include "image.h"
#include "spiral.h"
#include "attractor.h"
#include "attractor_connections.h"
#include "ikeda.h"
#include "polynomial.h"
#include "phi.h"

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

    /*POPRAWKA*/
    string opt = "X";

    if(argc >=2) config = argv[1];
    if(argc >=3)
    {
        cout<<argv[2] <<endl;
        /*POPRAWKA*/
        if(argv[2][0] == 'v') opt = "video";
        if(argv[2][0] == 'i') opt = "image";
    }
    cout<<"OPT: "<<opt<<endl;

    cout<<"Plik konfiguracyjny: "<<config<<endl;
    fstream file;
    string name;

    file.open(config, ios::in);

    if (file.is_open())
    {
        file>>name;
        file.close();
    } else
    {
        cout<<"Nie udało się otworzyć pliku: "<<config<<endl;
        return 0;

    }



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
    if(name == "#Spiral")
    {
        system = new Spiral();
    } else
    if(name == "#Attractor")
    {
        system = new Attractor();
    }else
    if(name == "#AttractorConnections")
    {
        system = new AttractorConnections();
    }else
    if(name == "#Ikeda")
    {
        system = new Ikeda();
    }else
    if(name == "#Polynomial")
    {
        system = new Polynomial();
    }else
    if(name == "#Phi")
    {
        system = new Phi();
    }
    else
    {
        ok  = false;
        cout<<"Nieznana animacja"<<endl;
    }


    if(ok)
    {
        cout<<"Animacja: "<<name<<endl;
        system->Load(config);

        /*POPRAWKA*/
        if(opt != "X") system->filetype=opt;

        system->Render();
    }

    return 0;
}

