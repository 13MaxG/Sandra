#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
#include <list>
#include <ctime>

#include "command.h"
#include "argument.h"
#include "video.h"
#include "convert.h"
#include "operator.h"
#include "image.h"

/**
 * @brief Główna klasa animacji.
 *
 * Zawiera wszystkie inormacje dotyczące animacji, przelicza je, oraz renderuje.
 * Jest to szablon, z niego powinny dziedziczyć właściwe animacjie.
 *
 */
class System
{
protected:
    std::string now;
    /**
     * @brief Operator na pliku wideo
     */
    Video video;
    /**
     * @brief Operator na pliku graficznym
     */
    Image image;

    /**
     * @brief Plik z konfiuracją
     */
    std::fstream file;

    /**
     * @brief Aktualna klatka
     */
    unsigned long long currentFrame;

    /**
     * @brief Całkowita ilość klatek
     */
    unsigned long long totalFrames;


    /**
     *@brief Po prostu delta
     */
    double delta;

    /**
     * @brief Typ pliku wyjściowego (avi lub png)
     */
   public:/*POPRAWKA*/
    std::string filetype;
protected:
    /**
     * @brief Nazwa pliku wyjściowego (bez rozszerzenia)
     */
    std::string filename;

    /**
     * @brief Czy tworzyć unikalne nazwy
     */
    bool diffrentNames;

    /**
     * @brief Szerokość klatki animacji lub obrazka
     */
    unsigned int width;

    /**
     * @brief Wysokość klatki animacji lub obrazka
     */
    unsigned int height;

    /**
     * @brief Poziom kompresji, 0 - bez, 9 maksymalna, tyczy się tylko PNG
     *
     */
    unsigned int compression;

    /**
     * @brief W którym momencie animacji, ma być renderowana klatka dla obrazu
     */
    double image_time;

    /**
     * @brief Ilosć klatek na sekundę
     */
    double fps;

    /**
     * @brief Długość animacji (w sekundach)
     */
    double time;

    /**
     * @brief Co ile mam informować o postępie
     *
     *  0 - wcale
     *  0.1 - co 10%
     */
    double process_info;
    double process_acc; // zmienna pomocnicza
    double process_total; // zmienna pomocznia
    bool process_show; // zmienna pomocnicza

    /**
     * @brief Kodek wideo
     *
     * "DVIX" - z kompresją
     * "I420" - bez kompresji, nie wszędzie działa
     * inne kodeki są takie jakie mogą być FOUR_CC z OpenCV
     */
    std::string codec;

    /**
     * @brief Repozytorium ze wskaźnikami do obiektów powiązanymi z nazwa
     *
     * Używane do wczytywania parametrów z plików.
     */
    Operator repository;


protected:
    /**
     * @brief Przygotuj argumenty (zmieniające się w czasie)
     */
    void PrepareArgs();

    /**
     * @brief Aktualizuj argumenty zmieniające się w czasie
     * @param dt Przyrost czasu
     */
    void UpdateArgs( double dt);

    /**
     * @brief Zbierz informacje dotyczące procesu
     */
    void ReadProcessInfo(double dt);

    /**
     * @brief Poinformuj o procesie
     */
    void WriteProcessInfo();

    /**
     * @brief Renderuj pojedynczą klatkę
     * @param Macierz na której jest renderowana klatka
     */
    virtual void DrawFrame(cv::Mat frame);

    /**
     * @brief Co się ma wykonać przed procesem renderowania
     *
     * Można wykorzystać do niestandardowego skonfigurowania parametrów
     */
    virtual void Before();

    /**
     * @brief Co się ma wykonać zaraz po zakończeniu renderowania
     */
    virtual void After();

public:
    System();
    virtual ~System(); // ma być, bo inaczej nie działa

    /**
     * @brief Wczytaj parametry
     * @param fileName nazwa pliku
     */
    void Load(char* fileName);

    /**
     * @brief Renderuj, z podanymi ustawieniami
     */
    void Render();

};

#endif // SYSTEM_H
