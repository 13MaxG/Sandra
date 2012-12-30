#include "system.h"
#include <iostream>

System::System()
{
    // Standardowo:
    diffrentNames = true;


    // Dodaję do repozytorium podstawowe parametry
    repository.Register("output_type", &filetype);
    repository.Register("output_file", &filename);
    repository.Register("diffrent_names", &diffrentNames);
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
    // Trololo :)
}

void System::Load(char *fileName)
{

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

        // Przekaż command do repozytorium, ono je obsłuży dokładniej
        // Jeżeli się nie uda, to powiadom o tym
        if(!repository.Add(&command))
        {
             std::cout<<"("<<i<<"): Nie znaleziono polecenia: "<<command.Name()<<std::endl;
        }


    }

}


void System::Render()
{
    // Dodaj coś do nazwy pliku
    if(diffrentNames)
        filename.append("_"+toString<int>(std::time(0)));

    // Gotuj! Mamo, nie mówiłem o parówkach!
    PrepareArgs();

    // Jeżeli chcecie orbrazek
    if(filetype == "image")
    {
        // to zrobię Wam go w cywilizowanym formacie
        filename.append(".png");

        image.SetWidth(width);
        image.SetHeight(height);
        image.SetCompression(compression);
        image.SetFileName(filename);

        // Ale rosołek może być! :)
        image.Prepare();

        // Tylko go nie zapomnij przyprawić.
        UpdateArgs(image_time);
        // A ja już go podam do stołu
        DrawFrame(image.Frame);

        // Tylko czy go doniosę nie rozlewając ani kropelki?
        image.RenderImage();

    } else
    if(filetype == "video") // Chcemy wideo
    {

        filename.append(".avi");

        // Oblicz całkowitą ilość klatek
        totalFrames = time * fps;
        // ale zacznij od zera
        currentFrame = 0;

        // Przyrost procesu po jedej klatce
        delta = 1.0 / totalFrames;

        // Informowanie o procesie renderowania
        double up = 0.05; // Co ile procent(tfu, no wiesz o co chodzi)
        double tmp = 0; // Jakaś pomocnicza zmienna
        double total = 0; // Całkowity proces

        // W miarę czytelne
        video.SetCodec(codec);
        video.SetResolutionWidth(width);
        video.SetResolutionHeight(height);
        video.SetFPS(fps);
        video.SetFileName(filename);
        video.Prepare(); // Mhmmm

        // Tak na wszelki wypadek
        UpdateArgs(0);



        // Początkowe wyświetlenie procesu
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


            // Opis SCENY
            DrawFrame(video.Frame);
            UpdateArgs(delta);

            // wyrenderuj!
            video.RenderFrame();


            tmp += delta;
            total +=delta;
        }
        // proces, proces, proces
        std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrame<<" <><> "<<currentFrame<<" / "<<totalFrames<<std::endl;

        std::cout<<"Ukończono renderowanie"<<std::endl;


    // użytkownik też robi błedy, nie tylko ty, więc pomyśl że może rozwalić Ci program
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
    // co za wstrętny warring, no przecież to funkcja wirtualna
    //  a bez tego by i tak strzelił focha, że nie da rady wykompilować


    // GCC! kim wy właściwie jesteś...
    // tym, czy tą...

    // lepiej skończmy, mam jeszcze dużo do komentowania
}

void System::Before()
{

}

void System::After()
{

}
