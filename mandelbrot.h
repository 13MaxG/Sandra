#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "system.h"

class Mandelbrot : public System
{
private:
    Argument<unsigned  int> iterations;

public:
    Mandelbrot();

    /**
     * @brief Wczytaj konfiguracje z pliku
     * @param fileName nazwa pliku z konfiguracją
     */
    void Load(char *fileName);
    /**
     * @brief Przygotuj zmienne
     */
    void Prepare();

    /**
     * @brief Auaktualnij zmienne
     * @param d przyrost procenu animacji(1 - 100%)
     */
    void Update(double d);

    /**
     * @brief Rendeuje animacje
     */
    void Render(double info);
};

#endif // MANDELBROT_H
