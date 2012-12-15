#include "system.h"
#include <iostream>

System::System()
{

}

System::~System()
{

}

void System::Load(char *fileName)
{
    totalFrames = 0;
    totalTime = 0;
    currentFrames = 0;
}

void System::Prepare()
{

}

void System::Update(double d)
{

}

void System::CreateFrame()
{

}

void System::BeforeRedner()
{

}

void System::Render(double info = 0.05)
{
    std::cout<<"Plik wyjściowy: "<<video.GetFileName()<<std::endl;
    std::cout<<"[pozostało w %] <=> [pozostało]  <><> [Ilość wyrenderowanych] / [Ilość wszytskich klatek] : "<<std::endl;

    // Do wyświetlania procesu
    double up = info;
    double tmp = 0;
    double total = 0;

    // Policz ostatnie rzeczy
    if(totalTime != 0) // jeżeli podano czas trwania animacji
    {
        // to oblicz ilość klatek
        totalFrames = video.GetFPS() * totalTime;

    }
    // delta do aktualizowania paremetrów
    delta = 1.0 / totalFrames;

    // Przygotuj argumenty
    Prepare();

    // Przygotuj wideo
    video.Prepare();

    BeforeRedner();


    std::cout.precision(2);

    std::cout<<(total)*100<<"% <=> "<<totalFrames <<" <><> "<<0<<" / "<<totalFrames<<std::endl;

    // Pętla przez wszytskie klatki
    for(currentFrames = 0; currentFrames < totalFrames; currentFrames++)
    {
        // Wyświetlanie procesu

        if(tmp >= up)
        {
            tmp = 0;
            std::cout<<std::fixed<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;
        }



        CreateFrame();
        // renderuj!
        video.RenderFrame();

        tmp += delta;
        total +=delta;
    }
    std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;

    std::cout<<"Ukończono renderowanie"<<std::endl;

}
