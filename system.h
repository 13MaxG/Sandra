#ifndef SYSTEM_H
#define SYSTEM_H

#include "argument.h"
#include "video.h"

/**
 * @brief Główna klasa animacji.
 *
 * Zawiera wszystkie inormacje dotyczące animacji, przelicza je, oraz renderuje.
 * Jest to szablon, z niego powinny dziedziczyć właściwe animacjie.
 */
class System
{
    Argument<double> x;
    Argument<double> y;
    Argument<double> r;

    Video video;

public:
    System();

     void Load();
     void Update();
     void Render();

};

#endif // SYSTEM_H
