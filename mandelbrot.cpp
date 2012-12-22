#include "mandelbrot.h"
#include <complex>

Mandelbrot::Mandelbrot()
{
}

void Mandelbrot::Load(char *fileName)
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
                 std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia: "<<command.NumbersOfArgument()<<std::endl;

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
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia: "<<command.NumbersOfArgument()<<std::endl;

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
                 std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia: "<<command.NumbersOfArgument()<<std::endl;

        } else
// czas trwania w klatkach
        if(command.Name() == "duration_frames")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalFrames = fromString< unsigned int > (command[0]);
            } else
                 std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia: "<<command.NumbersOfArgument()<<std::endl;

        } else


        if(command.Name() == "set_iterations")
        {
            if(command.NumbersOfArgument() == 2)
            {

                iterations.Set(Key<unsigned int>( fromString< unsigned int > (command[0]), fromString< double > (command[1])) );
            } else
                 std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia: "<<command.NumbersOfArgument()<<std::endl;

        }
// brak
        else
        {

            std::cout<<"("<<i<<"): Błąd: nie znaleziono polecenia"<<std::endl;
        }
    }
}

void Mandelbrot::Prepare()
{
    iterations.Prepare();
}

void Mandelbrot::Update(double d)
{
    iterations.Update(d);
}



void Mandelbrot::Render(double info)
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


        double frameHeight = video.GetResolutionHeight();
        double frameWidth = video.GetResolutionWidth();

        double pointX = 0.0, pointY=0.0; //
        double zoom = 1.0;

        double width; // Układ współrzednych, cześć rzeczywista
        double height; // -..- część urojona

        if(frameWidth > frameHeight)
        {
            height = 2.0  / zoom;
            width = (frameWidth / frameHeight) * height;
        } else
        {
            width = 3.5  / zoom;
            height = (frameHeight / frameWidth) * width;
        }

        double minRe, maxRe;
        double minIm, maxIm;

        minRe = pointX - width / 2.0;
        maxRe = pointX + width / 2.0;

        minIm = pointY - height / 2.0;
        maxIm = pointY + height / 2.0;

        unsigned int maxIterations = iterations.Get();

        std::cout<<"minRe: "<<minRe<<"; maxRe: "<<maxRe<<std::endl;
        std::cout<<"minIm: "<<minIm<<"; maxIm: "<<maxIm<<std::endl;


        /*

        double MinRe = -2.0;
        double MaxRe = 1.0;
        double MinIm = -1.2;
        double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
        double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
        double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);


        unsigned MaxIterations = iterations.Get();

        for(unsigned y=0; y<ImageHeight; ++y)
        {
            double c_im = MaxIm - y*Im_factor;
            for(unsigned x=0; x<ImageWidth; ++x)
            {
                double c_re = MinRe + x*Re_factor;

                double Z_re = c_re, Z_im = c_im;
                bool isInside = true;
                double per = 0;
                for(unsigned n=0; n<MaxIterations; ++n)
                {
                    double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                    if(Z_re2 + Z_im2 > 4)
                    {
                        isInside = false;

                        unsigned  char r= 0 , g = 0, b = 0;
                         per =((double(n))/ ((double)MaxIterations));
                                            if(per < 0.5)
                                            {
                                                r = ((per  / 0.5) * 255.0) ;
                                                g = 0;
                                                b = 0;
                                            } else
                                            {
                                                r = 255;
                                                g = (((per-0.5)/ 0.5) * 255.0) ;;
                                               b = (((per-0.5)/ 0.5) * 255.0) ;;
                                            }
                                          //  data[A.step*i + A.channels()*j + 0]
                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 0] = b;
                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x +1] = g;
                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 2] = r;
                                            // cv::rectangle( video.Frame, cv::Point(x, y), cv::Point(x+1, y+1), cv::Scalar(b, g, r), 0,);

                        break;
                    }
                    Z_im = 2*Z_re*Z_im + c_im;
                    Z_re = Z_re2 - Z_im2 + c_re;
                }
                if(isInside)
                {
                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 0] = 0;
                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x +1] = 0;
                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 2] = 0;
                    //cv::rectangle( video.Frame, cv::Point(x, y), cv::Point(x+1, y+1), cv::Scalar(255, 255, 0), 1);
                    //cv::cvSet2D(video.Frame, x, y, cv::Scalar(255, 255, 255));
                }
            }
        }
        */


        // wyrenderuj!
        video.RenderFrame();

        tmp += delta;
        total +=delta;
    }
    std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;

    std::cout<<"Ukończono renderowanie"<<std::endl;

}