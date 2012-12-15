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
    /**
     * @brief Operator na pliku wideo
     */
    Video video;
    /**
     * @brief Plik z konfiuracją
     */
    std::fstream file;

    /**
     * @brief Aktualna klatka
     */
    unsigned long long currentFrames;
    /**
     * @brief Całkowita ilość klatek
     */
    unsigned long long totalFrames;
    /**
     * @brief Czas trwania animacji
     */
    unsigned long long totalTime;

public:
    System();
    virtual ~System(); // ma być, bo inaczej nie działa

    /**
     * @brief Wczytaj konfiguracje
     */
    virtual void Load(char* fileName);

    /**
     * @brief Przygotuj zmienne
     */

    virtual void Prepare();
    /**
     * @brief Aktualizuj zmienne
     */

    virtual void Update(double d);
    /**
     * @brief Renderuj do pliku
     */
    virtual void Render();

};

#endif // SYSTEM_H
