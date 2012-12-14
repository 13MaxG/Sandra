#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

#include "command.h"
#include "argument.h"
#include "video.h"
#include "convert.h"

/**
 * @brief Główna klasa animacji.
 *
 * Zawiera wszystkie inormacje dotyczące animacji, przelicza je, oraz renderuje.
 * Jest to szablon, z niego powinny dziedziczyć właściwe animacjie.
 */
class System
{
protected:
    Video video;
    std::fstream file;

    unsigned long long currentFrames;
    unsigned long long totalFrames;
    unsigned long long totalTime;
public:
    System();
    virtual ~System();

    virtual void Load(char* fileName);
    virtual void Update();
    virtual void Render();

};

#endif // SYSTEM_H
