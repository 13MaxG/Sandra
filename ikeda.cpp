#include "ikeda.h"
#define _USE_MATH_DEFINES
#include <cmath>


Ikeda::Ikeda()
{
    precise_info = true;

    repository.Register("iterations", &iterations);

    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);

    repository.Register("u", &A_u);
}

void Ikeda::Before()
{


}

void Ikeda::After()
{

}

//double trunc(double d){ return (d>0) ? floor(d) : ceil(d) ; }

void Ikeda::DrawFrame(cv::Mat frame)
{

    double x0, y0, m0, x, y, z, z0, x00, y00;

    x00 = 1;
    y00= 1;
    x0 = 1;
    y0 = 1;
    z0 = 1;
    double u;

    u = A_u.Get();



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

    double m2 = 0;//color

    double t0 = 0;
    for(unsigned int iter = 0; iter < iterations.Get(); iter++)
    {

        t0 = 0.4 - 6 / (1+x0*x0 + y0*y0);

        x = 1 + u * (x0 * sin(t0) - y0*cos(t0));
        y = 1 + u * (x0 * cos(t0) - y0*cos(t0));

        z = sin(t0) + cos(t0);


        // m = (z  - min) /(max+min);   pamiętaj że (-1) - (-1) = 2
        m2 = (z + 2.0) / 4.0;



//        // INTERPOLACJA DWULINIOWA


        int imgx, imgy; // piksel na obrazie
        double dx, dy; // długości piksela na modelu
        double minx, miny; //minimalne wymiary modelu
        double maxx, maxy; // maksymalne wymiary modelu
        double errx, erry; // błędy dla x i y
                             //gdy a = 1 i c = 1, a * min(sin()) + c* min(sin())
        // dx = (max - min) / width
        // dx = ( ( a + c ) - ( -a + -c) ) / width
        // dy = ( ( e + g ) - ( -e + -g) ) / height

        //minx = -a-c; maxx = a+c;
        //miny = -e-g; maxy = e+g;
        minx = 0; maxx = 2;
        miny = 0; maxy = 2;
        dx = ( maxx - minx )/width;
        dy = ( maxy - miny )/height;

        imgx = trunc( (x - minx) / dx );
        imgy = trunc( (y - miny) / dy );

        errx = ( ( x - minx ) / dx ) - imgx;
        erry = ( ( y - miny ) / dy ) - imgy;

        if( imgx>=0 && imgx <width && imgy>=0 && imgy < height)
        {
            licznik[imgx][imgy] += (1.0 - errx) * (1.0 - erry) * m2;
            if(licznik[imgx][imgy] > maks)
                maks = licznik[imgx][imgy];
        }

        if( imgx+1>=0 && imgx+1 <width && imgy>=0 && imgy < height)
        {
            licznik[imgx+1][imgy] += (1.0 - errx) * (erry) * m2;
            if(licznik[imgx+1][imgy] > maks)
                maks = licznik[imgx+1][imgy];
        }

        if( imgx>=0 && imgx <width && imgy+1>=0 && imgy+1 < height)
        {
            licznik[imgx][imgy+1] += (errx) * (1.0-erry) * m2;
            if(licznik[imgx][imgy+1] > maks)
                maks = licznik[imgx][imgy+1];
        }

        if( imgx+1>=0 && imgx+1 <width && imgy+1>=0 && imgy+1 < height)
        {
            licznik[imgx+1][imgy+1] += (errx) * (erry) * m2;
            if(licznik[imgx+1][imgy+1] > maks)
                maks = licznik[imgx+1][imgy+1];
        }







        // BEZ INTERPOLACJI DWULINIOWEJ, Z ZAOKRĄGLENIEM
            //!!!!!!!!!!!!!!!
                // Pytanie: czy te ograniczniki będą działały
                // wystarczająco fajnie jeżeli ktoś poda parametry
                // skaldujące dla sinusów i cosinusów

        //int imgx, imgy;
       // imgx = round((x+(a+c))/(2 * (a+c)) * width);
       // imgy = round((y+(e+g))/(2 * (e+g)) * height);
        /*
        if(imgx <width && imgx>=0 && imgy < height && imgy>=0)
        {
            licznik[imgx][imgy]+=1;
            if(licznik[imgx][imgy] > maks) maks = licznik[imgx][imgy];
        }
        */


       // if(imgx>=0 && imgx < width && imgy >= 0 && imgy < height)
        //{
       //     frame.data[frame.step*imgy + frame.channels()* imgx + 0] = color_b.GetAbsolute(m);
       //     frame.data[frame.step*imgy + frame.channels()* imgx + 1] = color_g.GetAbsolute(m);
       //     frame.data[frame.step*imgy + frame.channels()* imgx + 2] = color_r.GetAbsolute(m);
       // }

        x00 = x0;
        y00 = y0;

        x0 = x;
        y0 = y;
        z0 = z;
        if(filetype == "video" && precise_info == true)
        {
            ReadProcessInfo((double)delta*(double)d2);
            //std::cout<<(double)delta/(double)iter<<", ### "<<process_total<<std::endl;
            WriteProcessInfo();
        }
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
            double m =  (licznik[x][y]) / (maks/2);

            frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*y + frame.channels()* x + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);


        }
    }

    for(int x = 0 ; x < width; x++)
    {
        delete licznik[x];
    }


}
