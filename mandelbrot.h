#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "system.h"

class Mandelbrot : public System
{
private:

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
     * @bierf Renderuj pojedynczą klatkę
     */
    void CreateFrame();
    /**
     * @brief pezed renderowaniem
     */
    void BeforeRedner();

    /**
     * @brief Auaktualnij zmienne
     * @param d przyrost procenu animacji(1 - 100%)
     */
    void Update(double d);
};

#endif // MANDELBROT_H
