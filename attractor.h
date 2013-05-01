#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include "system.h"


class Attractor : public System
{
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
