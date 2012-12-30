#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


/**
 * @brief Klasa operująca na pojedynczym pliku graficznym
 *
 * Ograniczenie: proszę używać tylko formatu PNG
 */
class Image
{
    /**
     * @brief Szerokość obrazka
     */
    unsigned int _width;

    /**
     * @brief  Wysokość obrazka
     */
    unsigned int _height;

    /**
     * @brief Nazwa obrazka
     */
    std::string _filename;

    /**
     * @brief Poziom kompresji
     */
    unsigned int _compression;

public:
    Image();

    /**
     * @brief Właściwa klatka do rysowania
     *
     * Musi być publiczna, nie ma co kombinować ze wskaźnikami
     * Tak jest po prostu lepiej
     */
    cv::Mat Frame;

    /**
     * @brief Przygotuj co trzeba
     *
     * Ażeby się wyspać trzeba sobie pościelić łoże
     */
    void Prepare();

    /**
     * @brief Rysuje obraz
     *
     * I śnić o pięknych rzeczach... albo kimś... tylko rano trzeba będzie odczekać
     */
    void RenderImage();

    /**
     * @brief Czyści klatkę
     *
     * Pff, i tak nic nie będziesz pamiętać
     */
    void ClearFrame();

    /**
     * @brief Ustawia szerokość
     *
     * Przecież miało być bez zbędnych setterów...
     * Dobra, może zrobie zabezpieczenia...
     * Gdyby komuś kiedyś przyszło do głowy żeby rozciągnąc obraz podczas rysowania
     */
    void SetWidth(unsigned int width);

    /**
     * @brief Zwraca szerokość
     */
    unsigned int GetWidth();

    /**
     * @brief Ustawia wysokość
     */
    void SetHeight(unsigned int height);

    /**
     * @brief Zwraca wysokość
     */
    unsigned int GetHeight();

    /**
     * @brief Ustawia nazwę pliku
     */
    void SetFileName(std::string filename);
    /**
     * @brief Zwraca nazwę pliku
     */
    std::string GetFileName();

    /**
     * @brief Ustawia poziom kompresji
     */
    void SetCompression(unsigned int compression);
    /**
     * @brief Zwraca poziom kompresji
     */
    unsigned int GetCompression();

};

#endif // IMAGE_H
