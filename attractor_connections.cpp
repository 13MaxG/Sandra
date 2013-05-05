#include "attractor_connections.h"


#define _USE_MATH_DEFINES
#include <cmath>


AttractorConnections::AttractorConnections()
{



    //automatic_clear_frame = false;
    precise_info = true;

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

    x00 = 1;
    y00= 1;
    x0 = 1;
    y0 = 1;
    z0 = 1;

    licznik = new double*[width];
       for(int x = 0 ; x < width; x++)
       {
           licznik[x] = new double[height];
           for(int y = 0; y < height; y++)
           {
               licznik[x][y] = 0;
           }
       }
    maks = 0;

}

void AttractorConnections::Before()
{


}

void AttractorConnections::After()
{
    for(int x = 0 ; x < width; x++)
    {
        delete licznik[x];
    }
}

//double trunc(double d){ return (d>0) ? floor(d) : ceil(d) ; }

void AttractorConnections::DrawFrame(cv::Mat frame)
{


    video.automatic_clear_frame = false;
    double a, b, c, d, e, f, g, h;

    a = A_a;
    b = A_b;
    c = A_c;
    d = A_d;
    e = A_e;
    f = A_f;
    g = A_g;
    h = A_h;


    Argument<double> color_r = c_r;
    Argument<double> color_g = c_g;
    Argument<double> color_b = c_b;

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();




    WriteProcessInfo();


    double m2 = 0;//color



       // x = a * sin( b * (y0 + x00)  ) + c * cos( d * (x0 + y00) );
        //y = e * sin( f * (x0 + y00) ) + g * cos( h * (y0 + x00) );

        x = a * sin( b * (y0 )  ) + c * cos( d * (x0 ) );
        y = e * sin( f * (x0 ) ) + g * cos( h * (y0) );

        z = sin(x0) + cos(z0);


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

        minx = -a-c; maxx = a+c;
        miny = -e-g; maxy = e+g;

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






        if( imgx>=0 && imgx <width && imgy>=0 && imgy < height)
        {
            double m =  (licznik[imgx][imgy]) / (maks);

            frame.data[frame.step*imgy + frame.channels()* imgx + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*imgy + frame.channels()* imgx + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*imgy + frame.channels()* imgx + 2] = color_r.GetAbsolute(m);
        }
        if( imgx+1>=0 && imgx+1 <width && imgy>=0 && imgy < height)
        {
            double m =  (licznik[(imgx+1)][imgy]) / (maks);

            frame.data[frame.step*imgy + frame.channels()* (imgx+1) + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*imgy + frame.channels()* (imgx+1) + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*imgy + frame.channels()* (imgx+1) + 2] = color_r.GetAbsolute(m);
        }
        if( imgx>=0 && imgx <width && imgy+1>=0 && imgy+1 < height)
        {
            double m =  (licznik[imgx][(imgy+1)]) / (maks);

            frame.data[frame.step*(imgy+1) + frame.channels()* imgx + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*(imgy+1) + frame.channels()* imgx + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*(imgy+1) + frame.channels()* imgx + 2] = color_r.GetAbsolute(m);
        }
        if( imgx+1>=0 && imgx+1 <width && imgy+1>=0 && imgy+1 < height)
        {
            double m =  (licznik[(imgx+1)][(imgy+1)]) / (maks);

            frame.data[frame.step*(imgy+1) + frame.channels()* (imgx+1) + 0] = color_b.GetAbsolute(m);
            frame.data[frame.step*(imgy+1) + frame.channels()* (imgx+1) + 1] = color_g.GetAbsolute(m);
            frame.data[frame.step*(imgy+1) + frame.channels()* (imgx+1) + 2] = color_r.GetAbsolute(m);
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









}
