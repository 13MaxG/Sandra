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

    /**
     *@brief Po prostu delta
     */
    double delta;

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
     * @bierf Stwórz pojedynczą klatkę
     *
     * Wylicza aktualną klatkę. Jest ona gotowa do wyrenderowania
     */
    virtual void CreateFrame();

    /**
     * @brief pezed renderowaniem
     *
     * Wpisać do niej rzec które powinny się oliczyć zamin zacznie się renderować.
     * (pętla z tworzeniem klatek)
     */
    virtual void BeforeRedner();

    /**
     * @brief Renderuj do pliku
     *
     * Renderuj do  pliku. Na początku przygotowuje parametry oraz wideo.
     * Potem wykonuje metodę BeforeRender(), którą można wirtualizować.
     * Następnie w pętli tworzy wszytskie klatki jakie mają być zamierzone.
     * Klatki tworzy metodą CreateFrame. Po stworzeniu każdej klatki jest ona zapisywana do pliku.
     *
     * Kiedyś można było stworzyć pochodną tej funkcji, ale uznałem że tak będzie mniej kopiowania.
     */
    void Render(double info);

};

#endif // SYSTEM_H
