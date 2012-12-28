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
 */
class System
{
protected:
    /**
     * @brief Operator na pliku wideo
     */
    Video video;
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

    std::string filetype;
    std::string filename;

    unsigned int width, height;

    unsigned int compression;
    double image_time;

    double fps;
    double time;
    std::string codec;

    Operator repository;

public:
    System();
    virtual ~System(); // ma być, bo inaczej nie działa

    void Load(char* fileName);
    void Render();

    void PrepareArgs();
    void UpdateArgs( double dt);

    virtual void DrawFrame(cv::Mat frame);
    virtual void Before();
    virtual void After();











//    /**
//     * @brief Wczytaj konfiguracje
//     */
//    virtual void Load(char* fileName);

//    /**
//     * @brief Przygotuj zmienne
//     */

//    virtual void Prepare();
//    /**
//     * @brief Aktualizuj zmienne
//     */

//    virtual void Update(double d);



//    /**
//     * @brief pezed renderowaniem
//     *
//     * Wpisać do niej rzec które powinny się oliczyć zamin zacznie się renderować.
//     * (pętla z tworzeniem klatek)
//     */
//    void BeforeRedner();

//    /**
//     * @brief Renderuj do pliku
//     *
//     * Renderuj do  pliku. Na początku przygotowuje parametry oraz wideo.
//     * Potem wykonuje metodę BeforeRender(), którą można wirtualizować.
//     * Następnie w pętli tworzy wszytskie klatki jakie mają być zamierzone.
//     * Klatki tworzy metodą CreateFrame. Po stworzeniu każdej klatki jest ona zapisywana do pliku.
//     *
//     * Nie jest rozbita na mniejsze podfukncje, dlatego że czasami możesz wymyślić jakieś optymalizacje, którym będą podfunkcje przeszkadzać.
//     * Niestety część kodu lepiej spokojnie przekopiować
//     */
//    virtual  void Render(double info);

};

#endif // SYSTEM_H
