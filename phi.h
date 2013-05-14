#ifndef PHI_H
#define PHI_H

#include "system.h"

class Phi : public System
{
private:
    Argument<unsigned  int> iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;

    Argument<double> A_a;
    Argument<double> A_b;

    Argument<double> Scale;

    double re(double x); // Wykres części rzeczywistej
    double im(double x); // Wykres części urojonej
    // funkcji f(x) = (-phi)^x; wzory obliczyłem z wolfram alpha

public:
    Phi();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // PHI_H
