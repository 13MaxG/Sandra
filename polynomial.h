#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "system.h"

class Polynomial : public System
{
private:
    Argument<unsigned  int> iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;

    // To niżej będą tablice.
    // Każda zawiera współczynniki dla jednego równania
    // Po 6 elementów na każdą, łącznie 18 bo trzy wymiary
    // Dla czytelności nie jest to dwuwymiarowa tablica
    Argument<double> *A;
    Argument<double> *B;
    Argument<double> *C;

    Argument<double> MINx, MINy;
    Argument<double> MAXx, MAXy;

public:
    Polynomial();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // POLYNOMIAL_H
