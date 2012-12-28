#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "system.h"

class Mandelbrot : public System
{
private:
    Argument<unsigned  int> iterations;

    std::string coloring;
    Argument<double> px, py;
    Argument<double> s;
    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;
    Argument<unsigned  int > max_iter ;

public:
    Mandelbrot();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // MANDELBROT_H
