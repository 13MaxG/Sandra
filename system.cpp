#include "system.h"
#include <iostream>

System::System()
{
    repository.Register("output_type", &filetype);
    repository.Register("output_file", &filename);
    repository.Register("width", &width);
    repository.Register("height", &height);
    repository.Register("compression", &compression);
    repository.Register("image_time", &image_time);
    repository.Register("fps", &fps);
    repository.Register("time", &time);
    repository.Register("codec", &codec);

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

        if(!repository.Add(&command))
        {
             std::cout<<"("<<i<<"): Nie znaleziono polecenia: "<<command.Name()<<std::endl;
        }


    }





}


void System::Render()
{
    PrepareArgs();
    if(filetype == "image")
    {
        image.SetWidth(width);
        image.SetHeight(height);
        image.SetCompression(compression);
        image.SetFileName(filename);

        image.Prepare();

        UpdateArgs(image_time);
        DrawFrame(image.Frame);

        image.RenderImage();

    } else
    if(filetype == "video")
    {


        totalFrames = time * fps;
        currentFrame = 0;

        delta = 1.0 / totalFrames;

            double up = 0.05;
            double tmp = 0;
            double total = 0;


            video.SetCodec(codec);
            video.SetResolutionWidth(width);
            video.SetResolutionHeight(height);
            video.SetFPS(fps);
            video.SetFileName(filename);
            video.Prepare();

            UpdateArgs(0);

            std::cout.precision(2);
            std::cout<<(total)*100<<"% <=> "<<totalFrames <<" <><> "<<0<<" / "<<totalFrames<<std::endl;

            // Pętla przez wszytskie klatki
            for(currentFrame = 0; currentFrame < totalFrames; currentFrame++)
            {
                // Wyświetlanie procesu

                if(tmp >= up)
                {
                    tmp = 0;
                    std::cout<<std::fixed<<(total)*100<<"% <=> "<<totalFrames - currentFrame<<" <><> "<<currentFrame<<" / "<<totalFrames<<std::endl;
                }


                // OpiS SCENY


                DrawFrame(video.Frame);
                UpdateArgs(delta);

                // wyrenderuj!
                video.RenderFrame();

                tmp += delta;
                total +=delta;
            }
            std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrame<<" <><> "<<currentFrame<<" / "<<totalFrames<<std::endl;

            std::cout<<"Ukończono renderowanie"<<std::endl;



    } else std::cout<<"Nieobsługiwalny typ, spójrz do pliku konfiguracyjnego"<<std::endl;

}

void System::PrepareArgs()
{
    repository.PrepareArgs();
}

void System::UpdateArgs(double dt)
{
    repository.UpdateArgs(dt);
}

void System::DrawFrame(cv::Mat frame)
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
