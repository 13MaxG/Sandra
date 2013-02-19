#ifndef SPIRAL_H
#define SPIRAL_H

#include "system.h"

class Spiral : public System
{

    int Pr;
    int Le;

    Argument<int> Pd, Ld;
    Argument<double> lim;

 Argument<double> *limsP;
 Argument<double> *limsL;

double *dP, *dL;
    Argument<double> procent;
     Argument<double> Scale;

     /**
      * @brief Kolor czerwony
      */
     Argument<double> color_r;
     /**
      * @brief Kolor zielony
      */
     Argument<double> color_g;
     /**
      * @brief Kolor niebieski
      */
     Argument<double> color_b;
Argument<double> Rotate;

public:
    Spiral();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // SPIRAL_H
