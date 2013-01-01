#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "system.h"

class Mandelbrot : public System
{
private:

    /**
     * @brief Ilość iteracji
     */
    Argument<unsigned  int> iterations;

    /**
     * @brief metoda kolorowania
     *
     * linear - liniowa z palety
     * logarithmic_sinus - logarytmiczna z sinusem
     */
    std::string coloring;

    /**
     * @brief Współrzędna X środka widoku
     */
    Argument<double> px;

    /**
     * @brief Współrzędna Y środka widoku
     */
    Argument<double> py;

    /**
     * @brief Skala obrazu
     */
    Argument<double> s;

    /**
     * @brief Czerwona paleta
     */
    Argument<double> c_r ;

    /**
     * @brief Zielona paleta
     */
    Argument<double> c_g ;

    /**
     * @brief Niebieska paleta
     */
    Argument<double> c_b ;

    /**
     * @brief Ilość iteracji
     */
    Argument<unsigned  int > max_iter ;

    double d2; // pomocznicza, do procesu dla image

    /**
     * @brief promień
     *
     * Zwykle starczy 2, chyba że sa problemy z logarytmicznym kolorowaniem
     */
    Argument<double> r;

    /**
     * @brief Czy życzysz sobie czarną dziurę czy może oświetloną?
     */
    bool hole;



public:
    Mandelbrot();

    // poczytaj w Sysem o tym
    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // MANDELBROT_H
