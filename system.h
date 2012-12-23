#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
#include <list>


#include "command.h"
#include "argument.h"
#include "video.h"
#include "convert.h"
#include "operator.h"


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


    //    std::map<std::string, Argument<double> > MapArgDouble;
    //    std::list<std::string> MapArgDoubleNames;

    //    std::map<std::string, Argument<int> > MapArgInt;
    //    std::list<std::string> MapArgIntNames;

    //    std::map<std::string, Argument<unsigned int> > MapArgUInt;
    //    std::list<std::string> MapArgUIntNames;

    //    std::map<std::string, double > MapDouble;
    //    std::list<std::string> MapDoubleNames;

    //    std::map<std::string, int > MapInt;
    //    std::list<std::string> MapIntNames;

    //    std::map<std::string, unsigned int > MapUInt;
    //    std::list<std::string> MapUIntNames;


    //    std::map<std::string, std::string > MapString;
    //    std::list<std::string> MapStringNames;

    //    std::map<std::string, bool > MapBool;
    //    std::list<std::string> MapBoolNames;

        std::map<std::string, double* > MapDouble;
        std::list<std::string> MapDoubleNames;

        Operator oper;

        double sqrt2;
        Argument<double> Piernik;

public:
    System();
    virtual ~System(); // ma być, bo inaczej nie działa

    void Load(char* fileName);
    void Render();

    void PrepareArgs();
    void UpdateArgs(double dt);

    virtual void DrawFrame(double dt);
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
