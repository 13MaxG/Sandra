#ifndef ATTRACTOR_CONNECTIONS_H
#define ATTRACTOR_CONNECTIONS_H

#include "system.h"

class AttractorConnections : public System
{
private:

    unsigned  int iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;


    double A_a;
    double A_b;
    double A_c;
    double A_d;

    double A_e;
    double A_f;
    double A_g;
    double A_h;

    double x0, y0, m0, x, y, z, z0, x00, y00;

    double **licznik;
    double maks;

public:
    AttractorConnections();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // ATTRACTOR_CONNECTIONS_H
