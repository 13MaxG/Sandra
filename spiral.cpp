#include "spiral.h"
#define _USE_MATH_DEFINES
#include <cmath>

Spiral::Spiral()
{
    repository.Register("lim", &lim);
}


void Spiral::Before()
{

}

void Spiral::After()
{

}


void Spiral::DrawFrame(cv::Mat frame)
{



    double midx = this->width / 2;
    double midy = this->height / 2;

    double phi = (sqrt(5) + 1 ) / 2.0;

    double x0 = 0, y0 = 0, x = 0, y=0;

    double alfa = 0;

    double s = 1;

    //double p = 2*M_PI * 3;
    double p = lim.Get();

    double n = 500;
    double deltaAlfa = (2*M_PI)/n;

    while(alfa < p)
    {
        double r = s * std::pow(M_E, std::log(phi) * alfa);

        x0 = x;
        y0 = y;

        x = r * cos(alfa);
        y = r * sin(alfa);

        alfa += deltaAlfa;

        cv::line(
            frame, // na klatce widea
            cv::Point(midx + x0, midy + y0), // od
            cv::Point(midx + x,midy+ y), // do
            cv::Scalar(12, 255, 137), // kolorem
            1, // o grubości 1
            CV_AA); // z aintialastiniem

    }



}
