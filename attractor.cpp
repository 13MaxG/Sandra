#include "attractor.h"
#define _USE_MATH_DEFINES
#include <cmath>


Attractor::Attractor()
{
    repository.Register("iterations", &iterations);

    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);

    repository.Register("a", &A_a);
    repository.Register("b", &A_b);
    repository.Register("c", &A_c);
    repository.Register("d", &A_d);

    repository.Register("e", &A_e);
    repository.Register("f", &A_f);
    repository.Register("g", &A_g);
    repository.Register("h", &A_h);

}

void Attractor::Before()
{


}

void Attractor::After()
{

}

void Attractor::DrawFrame(cv::Mat frame)
{

    double x0, y0, x, y;

    x0 = 1;
    y0 = 1;

    double a, b, c, d, e, f, g, h;

    a = A_a.Get();
    b = A_b.Get();
    c = A_c.Get();
    d = A_d.Get();
    e = A_e.Get();
    f = A_f.Get();
    g = A_g.Get();
    h = A_h.Get();


    Argument<double> color_r = c_r;
    Argument<double> color_g = c_g;
    Argument<double> color_b = c_b;

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();


    double **licznik = new double*[width];
    for(int x = 0 ; x < width; x++)
    {
        licznik[x] = new double[height];
        for(int y = 0; y < height; y++)
        {
            licznik[x][y] = 0;
        }
    }
    double maks = 0;

    WriteProcessInfo();

    double d2 = 1.0 / (double) iterations.Get() ;

    for(unsigned int iter = 0; iter < iterations.Get(); iter++)
    {

        x = a * sin( b * y0 ) + c * cos( d * x0 );
        y = e * sin( f * x0 ) + g * cos( h * y0 );

        int imgx, imgy;

        imgx = round((x+2)/4.0 * width);
        imgy = round((y+2)/4.0 * height);

        if(imgx <width && imgx>=0 && imgy < height && imgy>=0)
        {
            licznik[imgx][imgy]+=1;
            if(licznik[imgx][imgy] > maks) maks = licznik[imgx][imgy];
        }
        x0 = x;
        y0 = y;

        if(filetype == "image")
        {
            ReadProcessInfo(d2);
            WriteProcessInfo();
        }
    }


    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            double m =  (licznik[x][y]) / (maks);

            frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*y + frame.channels()* x + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);


        }
    }


}
