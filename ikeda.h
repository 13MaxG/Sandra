#ifndef IKEDA_H
#define IKEDA_H

#include "system.h"

class Ikeda: public System
{
private:

    Argument<unsigned  int> iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;


    Argument<double> A_u;

public:
    Ikeda();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};


#endif // IKEDA_H
