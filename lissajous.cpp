#include "lissajous.h"

Lissajous::Lissajous() : System()
{
    spiral = false;
}

void Lissajous::Load(char* fileName)
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

        // Ważny moment!
        // wczytywanie parametrów
// Dotyczące wideo

        // Nazwa pliku
        if(command.Name() == "video_file_name")
        {
            if(command.NumbersOfArgument() == 1)
            {
                video.SetFileName(command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Szerokość klatki
        if(command.Name() == "video_resolution_width")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetResolutionWidth(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Wysokość klatki
        if(command.Name() == "video_resolution_height")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetResolutionHeight(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Ilość klatek na sekundę
        if(command.Name() == "video_fps")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetFPS(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }  else
//KODEK
        if(command.Name() == "video_codec")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetCodec(command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Czas trwania
        if(command.Name() == "duration_time")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalTime = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// czas trwania w klatkach
        if(command.Name() == "duration_frames")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalFrames = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// ilość klatek animacji
        if(command.Name() == "duration_frames")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalFrames = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
/////////
// promień
        if(command.Name() == "radius_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                radius.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// skala osi x
        if(command.Name() == "scale_x_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                scale_x.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// skala osi y
        if(command.Name() == "scale_y_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                scale_y.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// współczynnik cosinusa
        if(command.Name() == "factor_x_cos_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                factor_x_cos.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }else
// współczynnik sinusa
        if(command.Name() == "factor_y_sin_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                factor_y_sin.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }  else
// rozmiar skoku
        if(command.Name() == "jump_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                jump.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Dokładność
        if(command.Name() == "precision_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                precision.Set(Key<unsigned int>(fromString< unsigned int > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// Ilość skoków
        if(command.Name() == "jumps_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                jumps.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// czerwono
        if(command.Name() == "color_r_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_r.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// zielono
        if(command.Name() == "color_g_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_g.Set(Key<double>(fromString< double> (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
// niebiesko
        if(command.Name() == "color_b_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_b.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }else
// czy spirala
        if(command.Name() == "set_spiral")
        {
            if(command.NumbersOfArgument() == 1)
            {
                 spiral = command[0] == "true";


            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }
/////////
// Brak
        else
        {

            std::cout<<"("<<i<<"): Błąd: nie znaleziono polecenia"<<std::endl;
        }

    }

    file.close();
}

void Lissajous::Prepare()
{
    radius.Prepare();
    scale_x.Prepare();
    scale_y.Prepare();
    factor_x_cos.Prepare();
    factor_y_sin.Prepare();
    jump.Prepare();
    precision.Prepare();
    jumps.Prepare();
    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();
}

void Lissajous::Update(double d)
{
    radius.Update(d);
    scale_x.Update(d);
    scale_y.Update(d);
    factor_x_cos.Update(d);
    factor_y_sin.Update(d);
    jump.Update(d);
    precision.Update(d);
    jumps.Update(d);
    color_r.Update(d);
    color_g.Update(d);
    color_b.Update(d);
}



void Lissajous::Render(double info = 0.05)
{
    // Do wyświetlania procesu
    double up = info;
    double tmp = 0;
    double total = 0;

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


        // OpiS SCENY

        Update(delta); // aktualizuj parametry

        // Incepcja! Chcę aby krzywa była pokolorowana wegług podanej plaety
        Argument<double> color_r2 = color_r;
        Argument<double> color_g2 = color_g;
        Argument<double> color_b2 = color_b;

        // Muszę przygotować
        color_r2.Prepare();
        color_g2.Prepare();
        color_b2.Prepare();


        // delta dla kolorów w incepcji
        double d2 = (1.0 / precision.Get());
        if(spiral) d2 /= jumps.Get(); // troszkę inaczej to wygląda dla spirali
        //
        double alpha = 0; // aktualny kąt kreślenia okręgu
        double dAlpha = 2.0 * M_PI / precision.Get(); // delta kąta

        // Pozycje punktów
        double x = 0, y = 0;
        double x0 = 0, y0 = 0;

        // Promień
        double r;
        double rr = radius.Get(); // taka tak kopia
        // W przypadku spirali promień się będzie zmieniać
        if(spiral) r = 0; else r = rr;

        double jj; // Iloć skoków pętli dużej
        if(spiral) jj = jumps.Get(); else jj = 1;

        for(int j = 0; j < jj; j++) // pętla duża, do spirali
        for(int i = 0; i < precision.Get(); i++) // pętla mała, dokładność
        {


            // kąt
            alpha += dAlpha;

            // kolor
            color_r2.Update(d2);
            color_g2.Update(d2);
            color_b2.Update(d2);

            // promień
            if(spiral) r += jump.Get() / precision.Get() * rr;

            // punkty
            x0 = x;
            y0 = y;

            x = (video.GetResolutionWidth()/2)
                    + r * scale_x.Get() * cos(alpha * factor_x_cos.Get());
            y = (video.GetResolutionHeight()/2)
                    + r * scale_y.Get() * sin(alpha * factor_y_sin.Get());

            // jeżeli trzeba rysować to rysuj
            if(i>0 || j != 0 )
            cv::line(
                video.Frame, // na klatce widea
                cv::Point(x0, y0), // od
                cv::Point(x,y), // do
                cv::Scalar(color_b2.Get(), color_g2.Get(), color_r2.Get()), // kolorem
                1, // o grubości 1
                CV_AA); // z aintialastiniem


        }

        // wyrenderuj!
        video.RenderFrame();

        tmp += delta;
        total +=delta;
    }
    std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;

    std::cout<<"Ukończono renderowanie"<<std::endl;

}


