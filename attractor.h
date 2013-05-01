#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include "system.h"


class Attractor : public System
{
private:

    Argument<unsigned  int> iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;


    Argument<double> A_a;
    Argument<double> A_b;
    Argument<double> A_c;
    Argument<double> A_d;

    Argument<double> A_e;
    Argument<double> A_f;
    Argument<double> A_g;
    Argument<double> A_h;

public:
    Attractor();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // ATTRACTOR_H
