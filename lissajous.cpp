#include "lissajous.h"

Lissajous::Lissajous() : System()
{
    spiral = false;

    repository.Register("radius", &radius);
    repository.Register("scale_x", &scale_x);
    repository.Register("scale_y", &scale_y);
    repository.Register("factor_x_cos", &factor_x_cos);
    repository.Register("factor_y_sin", &factor_y_sin);
    repository.Register("jump", &jump);
    repository.Register("precision", &precision);
    repository.Register("jumps", &jumps);
    repository.Register("color_r", &color_r);
    repository.Register("color_g", &color_g);
    repository.Register("color_b", &color_b);
    repository.Register("spiral", &spiral);

}

void Lissajous::Before()
{

}

void Lissajous::After()
{

}


void Lissajous::DrawFrame(cv::Mat frame)
{
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

        x = width  / 2.0 + r * scale_x.Get() * cos(alpha * factor_x_cos.Get());
        y = height / 2.0 + r * scale_y.Get() * sin(alpha * factor_y_sin.Get());

        // jeżeli trzeba rysować to rysuj
        if(i>0 || j != 0 )
        cv::line(
            frame, // na klatce widea
            cv::Point(x0, y0), // od
            cv::Point(x,y), // do
            cv::Scalar(color_b2.Get(), color_g2.Get(), color_r2.Get()), // kolorem
            1, // o grubości 1
            CV_AA); // z aintialastiniem


    }








    /*
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

    std::cout<<"Ukończono renderowanie"<<std::endl;*/

}


