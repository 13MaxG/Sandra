#include "polynomial.h"
#define _USE_MATH_DEFINES
#include <cmath>

Polynomial::Polynomial()
{
    //automatic_clear_frame = true;//czyść klatkę po wyrenderowaniu
    precise_info = true;

    repository.Register("iterations", &iterations);

    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);

    // Dla 2D po 6, dla 3D po 10
    A = new Argument<double>[10];
    B = new Argument<double>[10];
    C = new Argument<double>[10];
    for(int i = 1; i <= 10; i++)
        repository.Register("a"+toString(i), &A[i-1]);
    for(int i = 1; i <= 10; i++)
        repository.Register("b"+toString(i), &B[i-1]);
    for(int i = 1; i <= 10; i++)
        repository.Register("c"+toString(i), &C[i-1]);

    repository.Register("MINx", &MINx);
    repository.Register("MINy", &MINy);
    repository.Register("MAXx", &MAXx);
    repository.Register("MAXy", &MAXy);
}

void Polynomial::Before()
{


}

void Polynomial::After()
{

}

void Polynomial::DrawFrame(cv::Mat frame)
{
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
    double min = 0;

    WriteProcessInfo();

    double d2 = 1.0 / (double) iterations.Get() ;

        double m2 = 0;//color
    double x = 1, y = 1, z = 1, x0 = 0, y0 = 0, z0 = 0;

    for(unsigned int iter = 0; iter < iterations.Get(); iter++)
    {
        ///DWA WYMIARY:
        ////x = A[0].Get() + A[1].Get()*x0 + A[2].Get()*x0*x0+A[3].Get()*x0*y0 + A[4].Get()*y0 + A[5].Get()*y0*y0;
        ////y = B[0].Get() + B[1].Get()*x0 + B[2].Get()*x0*x0+B[3].Get()*x0*y0 + B[4].Get()*y0 + B[5].Get()*y0*y0;
        ////x = A[0].Get() + A[1].Get()*x0 + A[2].Get()*x0*x0+A[3].Get()*x0*y0 + A[4].Get()*y0 + A[5].Get()*y0*y0;


        std::cout<<x<<", "<<y<<", "<<z<<std::endl;
        double qq;
        std::cin>>qq;
        // TRZY WYMIARY
        x = A[0].Get() + A[1].Get()*x0 + A[2].Get()*x0*x0+A[3].Get()*x0*y0+A[4].Get()*x0*z0 + A[5].Get()*y0 + A[6].Get()*y0*y0 + A[7].Get()*y0*z0 + A[8].Get()*z0+A[9].Get()*z0*z0;
        y = B[0].Get() + B[1].Get()*x0 + B[2].Get()*x0*x0+B[3].Get()*x0*y0+B[4].Get()*x0*z0 + B[5].Get()*y0 + B[6].Get()*y0*y0 + B[7].Get()*y0*z0 + B[8].Get()*z0+B[9].Get()*z0*z0;
        z = C[0].Get() + C[1].Get()*x0 + C[2].Get()*x0*x0+C[3].Get()*x0*y0+C[4].Get()*x0*z0 + C[5].Get()*y0 + C[6].Get()*y0*y0 + C[7].Get()*y0*z0 + C[8].Get()*z0+C[9].Get()*z0*z0;

        x0 = x;
        y0 = y;
        z0 = z;



//        std::cout<<x<<", "<<y<<std::endl;

//        for(int i = 1; i <= 10; i++)
//            std::cout<<A[i-1].Get()<<", ";
//        std::cout<<std::endl;

//        for(int i = 1; i <= 10; i++)
//            std::cout<<B[i-1].Get()<<", ";
//        std::cout<<std::endl;

//        for(int i = 1; i <= 10; i++)
//            std::cout<<C[i-1].Get()<<", ";
//        std::cout<<std::endl;

        //        // INTERPOLACJA DWULINIOWA


                int imgx, imgy; // piksel na obrazie
                double dx, dy; // długości piksela na modelu
                double minx, miny; //minimalne wymiary modelu
                double maxx, maxy; // maksymalne wymiary modelu
                double errx, erry; // błędy dla x i y

                minx = MINx.Get();
                miny = MINy.Get();
                maxx = MAXx.Get();
                maxy = MAXy.Get();


               // if(x >= minx && x <=maxx && y >= miny && y <=maxy)
                {

                    //gdy a = 1 i c = 1, a * min(sin()) + c* min(sin())
                    // dx = (max - min) / width
                    // dx = ( ( a + c ) - ( -a + -c) ) / width
                    // dy = ( ( e + g ) - ( -e + -g) ) / height

                   // minx = -a-c; maxx = a+c;
                    //miny = -e-g; maxy = e+g;

                    dx = ( maxx - minx )/width;
                    dy = ( maxy - miny )/height;

                    imgx = trunc( (x - minx) / dx );
                    imgy = trunc( (y - miny) / dy );

                    errx = ( ( x - minx ) / dx ) - imgx;
                    erry = ( ( y - miny ) / dy ) - imgy;

                    if( imgx>=0 && imgx <width && imgy>=0 && imgy < height)
                    {
                        m2 = (1.0 - errx) * (1.0 - erry) * z;

                        if( m2 > licznik[imgx][imgy])
                        {
                            licznik[imgx][imgy] = m2;

                            if(m2 > maks) maks = m2;
                            if(m2 < min) min = m2;
                        }

                    }

                    if( imgx+1>=0 && imgx+1 <width && imgy>=0 && imgy < height)
                    {
                        m2= (1.0 - errx) * (erry) * z;

                        if( m2 > licznik[imgx+1][imgy])
                        {
                            licznik[imgx+1][imgy] = m2;

                            if(m2 > maks) maks = m2;
                            if(m2 < min) min = m2;
                        }

                    }

                    if( imgx>=0 && imgx <width && imgy+1>=0 && imgy+1 < height)
                    {
                        m2 = (errx) * (1.0-erry) * z;

                        if( m2 > licznik[imgx][imgy+1])
                        {
                            licznik[imgx][imgy+1] = m2;

                            if(m2 > maks) maks = m2;
                            if(m2 < min) min = m2;
                        }


                    }

                    if( imgx+1>=0 && imgx+1 <width && imgy+1>=0 && imgy+1 < height)
                    {
                        m2 = (errx) * (erry) * z;

                        if( m2 > licznik[imgx+1][imgy+1])
                        {
                            licznik[imgx+1][imgy+1] = m2;

                            if(m2 > maks) maks = m2;
                            if(m2 < min) min = m2;
                        }

                    }


                }









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
            double m =  (licznik[x][y] - min) / (maks - min);

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
