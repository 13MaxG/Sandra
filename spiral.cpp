#include "spiral.h"
#define _USE_MATH_DEFINES
#include <cmath>

/*
 *#Spiral

process_info(0.05)

# Parametry wyjścia
output_type("video")
output_file("spiral")
width(987)
height(610)
fps( 25.0 )
time( 45 )
codec("DIVX"); I420 DIVX

# Parametry pokazu


lim(1.0, 0.0);
lim(7.25, 0.15);
lim(9.25, 0.8);
lim(9.25, 1.0);
Pr(13);
Le(21);
Ld(0, 0.0);
Ld(21, 0.1);
Ld(21, 1.0);
Pd(0.0, 0.0);
Pd(0, 0.15);
Pd(13, 0.40);
Pd(13, 1.0);
procent(0, 0.0);
procent(1, 1.0);
Scale(35.0, 0.0);
Scale(25.0, 0.5);
Scale(7.0, 0.95);
Scale(7.0, 1.0);


Rotate(0.0, 0.0);
Rotate(3.141592, 0.95);
Rotate(3.141592, 1.0);

##### KOLOR
# 1

color_r(0, 0.0);
color_g(0, 0.0);
color_b(0, 0.0);


color_r(255, 0.16);
color_g(0, 0.16);
color_b(0, 0.16);
# 2
color_r(255, 0.2666);
color_g(0, 0.2666);
color_b(255, 0.2666);
# 3
color_r(50, 0.4333);
color_g(50, 0.4333);
color_b(255, 0.4333);
# 4
color_r(0, 0.6);
color_g(255, 0.6);
color_b(255, 0.6);
# 5
color_r(0, 0.7666);
color_g(255, 0.7666);
color_b(0, 0.7666);
# 6
color_r(255, 0.8333);
color_g(255, 0.8333);
color_b(0, 0.8333);
# 7
color_r(0, 1.0);
color_g(0, 1.0);
color_b(0, 1.0);
###

 */
Spiral::Spiral()
{
    repository.Register("lim", &lim);
    repository.Register("Pr", &Pr);
    repository.Register("Le", &Le);

    repository.Register("Ld", &Ld);
        repository.Register("Pd", &Pd);

    repository.Register("procent", &procent);
    repository.Register("Scale", &Scale);

    repository.Register("color_r", &color_r);
    repository.Register("color_g", &color_g);
    repository.Register("color_b", &color_b);

    repository.Register("Rotate", &Rotate);


    dP = new double [100];

    for(int i = 0; i < 100; i++)
    {

        dP[i]=0.0;
    }

dL = new double [100];
    for(int i = 0; i < 100; i++)
    {

        dL[i]=0.0;
    }

}


void Spiral::Before()
{


}

void Spiral::After()
{

}


void Spiral::DrawFrame(cv::Mat frame)
{



    Argument<double> color_r2 = color_r;
    Argument<double> color_g2 = color_g;
    Argument<double> color_b2 = color_b;

    // Muszę przygotować
    color_r2.Prepare();
    color_g2.Prepare();
    color_b2.Prepare();



    double midx = this->width / 2;
    double midy = this->height / 2;

    double phi = (sqrt(5) + 1 ) / 2.0;



    double alfa = 0;

    double s = -2 + Scale.Get();

    //double p = 2*M_PI * 3;
    double p = lim.Get();

    double n = 100;
    double deltaAlfa = (2.0*M_PI)/(double)100;

    double start = 0;


    double rotate = Rotate.Get();

    start = 0;
    for(int a = 0; a < Ld.Get(); a++)
    {
        if(dL[a] < 1.0)
            dL[a]+=0.05;

        //limsL[a].Get() *
       // if(procent.Get() / 0.8 < (double)a / (double)Pr)
        //   break;



       // start += ;
            alfa = 0;
                double x0 = 0, y0 = 0, x = 0, y=0;
                while(alfa   <  dL[a] * p )
            {

                    double stage = alfa / p;
                double r = s * std::pow(M_E, std::log(phi)  * alfa);

                x0 = x;
                y0 = y;

                x = r * cos( ( alfa) - start - rotate);
                y = -r * sin(  (alfa) - start - rotate);

                alfa += deltaAlfa * 0.6;
                if((y0 == 0 && x0==0) || (x==0 && y ==0)) continue;
                cv::line(
                    frame, // na klatce widea
                    cv::Point(midx + x0, midy + y0), // od
                    cv::Point(midx + x,midy+ y), // do
                    cv::Scalar(color_b2.GetAbsolute(stage), color_g2.GetAbsolute(stage), color_r2.GetAbsolute(stage)), // kolorem
                    1, // o grubości 1
                    CV_AA); // z aintialastiniem

            }
            start += 2 * M_PI / (Le);
    }

    start = 0;
    for(int a = 0; a < Pd.Get(); a++)
    {
         if(dL[20] >= 1.0)
         {
        if(dP[a] < 1.0)
            dP[a]+=0.01;

       // if(procent.Get() / 0.8 < (double)a / (double)Pr)
        //   break;



       // start += ;
            alfa = 0;
                double x0 = 0, y0 = 0, x = 0, y=0;
                while(alfa   <dP[a]* p  )
            {
                            double stage =  (alfa / p);
                double r = s * std::pow(M_E, std::log(phi) * alfa);

                x0 = x;
                y0 = y;

                x = r * cos(start + alfa + rotate);
                y = r * sin(start +  alfa + rotate);

                alfa += deltaAlfa* 0.8;

                cv::line(
                    frame, // na klatce widea
                    cv::Point(midx + x0, midy + y0), // od
                    cv::Point(midx + x,midy+ y), // do
                    cv::Scalar(color_b2.GetAbsolute(stage), color_g2.GetAbsolute(stage), color_r2.GetAbsolute(stage)), // kolorem
                    1, // o grubości 1
                    CV_AA); // z aintialastiniem

            }
            start += 2 * M_PI / (Pr);
         }
    }

}
