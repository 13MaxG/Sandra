#ifndef SPIRAL_H
#define SPIRAL_H

#include "system.h"

class Spiral : public System
{

    Argument<double> lim;
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
