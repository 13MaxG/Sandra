#ifndef SIEVE_H
#define SIEVE_H

#include "system.h"


class point
{
public:
    double x, y;
    point()
    {
        x = 0; y = 0;
    }
    point(double X, double Y)
    {
        x = X;
        y = Y;
    }
};


class Sieve : public System
{
private:


    unsigned  int iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;


    point *data;
    point Q, B;


    int n; // ilość boków
    bool random; // losowe położenie wierzchołków
    bool points; // czy punkty czy linie(gdy fałsz)
    bool liczniki;

   // double **licznik;
    cv::Mat overall;


    double **licznik;
    double maks;


public:
    Sieve();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // SIEVE_H
