#include "system.h"
#include <iostream>

System::System()
{
    MapDoubleNames.push_back("sqrt2");
    MapDouble["sqrt2"] = &sqrt2;

    oper.Register("sqrt2", &sqrt2);
    oper.Register("piernik", &Piernik);
}

System::~System()
{

}

void System::Load(char *fileName)
{
    bool exist = true;

    // Otwórz plik z koniguracją
    file.open(fileName, std::ios::in);

    std::string line; // pojedyna linia
    Command command; // analizowanie polecenia

    int i = 0; // linia nr...
    while(true)
    {
        i++;
        std::getline(file, line); // wcztaj jedną linijkę
        if(file.eof()) break; // skończ jeżeli trzeba

        command.Analize(line, i); // przeanalizuj

        // jeżeli coś jest nie wporządku to pomiń polecenie
        if(!command.isOk()) continue;


        if(oper.Add(&command))
        {
            std::cout<<"MAM: "<<command.Name()<<std::endl;
        } else  std::cout<<"Nie znaleziono"<<std::endl;



//        for(std::list<std::string>::iterator iter = MapArgDoubleNames.begin(); iter  != MapArgDoubleNames.end(); ++iter)
//        {
//            if((*iter) == command.Name())
//            {
//                if(command.NumbersOfArgument() == 2)
//                {

//                    MapArgDouble[(*iter)].Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

//                } else
//                    std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

//            }
//        }
       // if(exist == false)
           // std::cout<<"Nie znaleziono polecenia"<<std::endl;
    }





}


void System::Render()
{
    std::cout<<sqrt2<<std::endl;

    Piernik.Prepare();

    for(int i = 0; i <= 10; i++)
    {
        std::cout<<Piernik.Get()<<std::endl;
        Piernik.Update(1.0/10.0);

    }
}

void System::PrepareArgs()
{

}

void System::UpdateArgs(double dt)
{

}

void System::DrawFrame(double dt)
{

}

void System::Before()
{

}

void System::After()
{

}

//void System::Load(char *fileName)
//{
//    totalFrames = 0;
//    totalTime = 0;
//    currentFrames = 0;
//}

//void System::Prepare()
//{

//}

//void System::Update(double d)
//{

//}


//void System::BeforeRedner()
//{
//    std::cout<<"Plik wyjściowy: "<<video.GetFileName()<<std::endl;
//    std::cout<<"Kodek: "<<video.GetCodec()<<std::endl;
//    std::cout<<"[pozostało w %] <=> [pozostało]  <><> [Ilość wyrenderowanych] / [Ilość wszytskich klatek] : "<<std::endl;



//    // Policz ostatnie rzeczy
//    if(totalTime != 0) // jeżeli podano czas trwania animacji
//    {
//        // to oblicz ilość klatek
//        totalFrames = video.GetFPS() * totalTime;

//    }
//    // delta do aktualizowania paremetrów
//    delta = 1.0 / totalFrames;

//    // Przygotuj argumenty
//    Prepare();

//    // Przygotuj wideo
//    video.Prepare();
//}

//void System::Render(double info = 0.05)
//{
//    // Do wyświetlania procesu
//    double up = info;
//    double tmp = 0;
//    double total = 0;

//    BeforeRedner();

//    std::cout.precision(2);

//    std::cout<<(total)*100<<"% <=> "<<totalFrames <<" <><> "<<0<<" / "<<totalFrames<<std::endl;

//    // Pętla przez wszytskie klatki
//    for(currentFrames = 0; currentFrames < totalFrames; currentFrames++)
//    {
//        // Wyświetlanie procesu

//        if(tmp >= up)
//        {
//            tmp = 0;
//            std::cout<<std::fixed<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;
//        }


//        // OpiS SCENY



//        // wyrenderuj!
//        video.RenderFrame();

//        tmp += delta;
//        total +=delta;
//    }
//    std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;

//    std::cout<<"Ukończono renderowanie"<<std::endl;

//}
