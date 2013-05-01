#include "system.h"
#include <iostream>

System::System()
{
    // Standardowo:
    diffrentNames = true;
    process_info = 0.05;

    process_acc = 0;
    process_total = 0;
    process_show = true;



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
    repository.Register("process_info", &process_info);
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

    file.close();
    file.open(fileName, std::ios::in);


    time_t rawtime;
    struct tm * timeinfo;

    std::time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    now =  toString( std::time (NULL) );


    std::string tmp = filename;
    tmp += "_config_"  + now + ".txt";
    std::fstream configCopy;
    configCopy.open(tmp.c_str(), std::ios::out);




    while(true)
    {
        std::getline(file, line); // wcztaj jedną linijkę
        configCopy << line<<std::endl;
        if(file.eof()) break;

    }

    file.close();
    configCopy.close();

}


void System::Render()
{


    // Dodaj coś do nazwy pliku
    if(diffrentNames)
        filename.append("_"+now);

    // Gotuj! Mamo, nie mówiłem o parówkach!
    PrepareArgs();

    std::cout<<"Typ wyjścia: "<<filetype<<std::endl;
    // Jeżeli chcecie orbrazek
    if(filetype == "image")
    {
        // to zrobię Wam go w cywilizowanym formacie
        filename.append(".png");

        image.SetWidth(width);
        image.SetHeight(height);
        image.SetCompression(compression);
        image.SetFileName(filename);

        std::cout<<"Kompresja: "<<compression<<std::endl;
        std::cout<<"Plik wyjściowy: "<<filename<<std::endl;

        std::cout<<std::endl;

        // Ale rosołek może być! :)
        image.Prepare();

        // Tylko go nie zapomnij przyprawić.
        UpdateArgs(image_time);

        std::cout<< "Renderowanie: "<<std::endl;
        Before();
        // A ja już go podam do stołu
        DrawFrame(image.Frame);
        After();
        std::cout<< "Ukończono renderowanie!"<<std::endl;
        std::cout<< "Zapisywanie. "<<std::endl;
        // Tylko czy go doniosę nie rozlewając ani kropelki?
        image.RenderImage();
        std::cout<< "Ukończono."<<std::endl;

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


        // W miarę czytelne

        video.SetCodec(codec);
        video.SetResolutionWidth(width);
        video.SetResolutionHeight(height);
        video.SetFPS(fps);
        video.SetFileName(filename);
        video.Prepare(); // Mhmmm

        std::cout<<"Czas trwania: "<<time<<" sekund "<<std::endl;
        std::cout<<"FPS: "<<fps<<std::endl;
        std::cout<<"Ilość klatek: "<<totalFrames<<std::endl;
        std::cout<<"Kodek: "<<codec<<std::endl;
        std::cout<<"Plik wyjściowy: "<<filename<<std::endl;

        std::cout<<std::endl;

        // Tak na wszelki wypadek
        UpdateArgs(0);


        std::cout<< "Renderowanie: "<<std::endl;
        Before();
        // Początkowe wyświetlenie procesu
        WriteProcessInfo();

        // Pętla przez wszytskie klatki
        for(currentFrame = 0; currentFrame < totalFrames; currentFrame++)
        {

            WriteProcessInfo();


            // Opis SCENY
            DrawFrame(video.Frame);
            UpdateArgs(delta);

            // wyrenderuj!
            video.RenderFrame();

            ReadProcessInfo(delta);
        }
        // proces, proces, proces
        WriteProcessInfo();
        After();
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


void System::ReadProcessInfo(double dt)
{
    process_acc += dt;
    process_total += dt;
    if(process_total > 1.0 ) process_total = 1.0;
    if(process_acc >= process_info)
    {
        process_show = true;
        process_acc = 0;

    }
}

void System::WriteProcessInfo()
{
    if(process_show)
    {
        process_show = false;
        std::cout<<process_total * 100.0 << " %"<<std::endl;
    }
}
