#ifndef LISSAJOUS_H
#define LISSAJOUS_H

#include "system.h"

class Lissajous : public System
{
    Argument<double> radius;
    Argument<double> scale_x;
    Argument<double> scale_y;
    Argument<double> factor_x_cos;
    Argument<double> factor_y_sin;
    Argument<double> jump;
    Argument<unsigned int> precision;
    Argument<unsigned int> jumps;

    Argument<double> color_r;
    Argument<double> color_g;
    Argument<double> color_b;

    double delta;
    bool spiral;

public:
    Lissajous();

    void Load(char *fileName);
    void Update();
    void Render();
};

#endif // LISSAJOUS_H
