#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <opencv2/core/core.hpp>        // cv::Mat
#include <opencv2/highgui/highgui.hpp>  // Video writer

/**
 * @brief Klasa operująca na pliku wideo.
 *
 * Pozwala na utworzenie pliku wideo w formacie AVI.
 * Umożliwia na tworzenie kolejnych klatek filmu. Na klatkach można rysować prymitywy.
 *
 * Użycie: Zeklarować, ustawić wartości, i renderować za pomocą metod z cv:: do Frame
 */
class Video
{
private:

/* Informacje */
    /**
     * @brief Informacja o zablokowaniu edycji parametrów
     */
    bool _lock;
    /**
     * @brief Nazwa pliku
     */
    std::string _filename;
    /**
     * @brief Szerokość klatek
     */
    unsigned int _width;
    /**
     * @brief Wysokość klatek
     */
    unsigned int _height;
    /**
     * @brief Użyty kodek do zapisu
     */
    std::string _codec;
    /**
     * @brief Ilość klatek na sekundę
     */
    unsigned int _fps;

/* OpenCV */
    /**
    * @brief Czarodziej :)
    */
    cv::VideoWriter _writer;

public:

/* OpenCV */
    /**
    * @brief Klatka po której należy rysować
    */
    cv::Mat Frame;

/* Podstawa */
    /**
    * @brief Konstruktor
    */
    Video();

/* Zarządzanie */
    /**
    * @brief Przygotuj do działania
    */
    void Prepare();

    /**
    * @brief Zwalnia blokadę zmiany wartości
    *
    * Może się przydać przy wielokrotnym wykorzystaniu obiektu. Nie przewiduję takiej potrzeby.
    */
    void Restart();

    /**
    * @brief Czyści aktualną klatkę
    *
    * Używać tylko do ewentualnych poprawek. Automatyczne czyszczenie zapewnia RenderFrame();
    */
    void ClearFrame();

    /**
    * @brief Renderuje klatkę i zapisuje do pliku
    */
    void RenderFrame();

/* Settery i Gettery */
    /**
    * @brief Sprawdza czy zmiana parametrów jest możliwa
    */
    bool IsLocked();

    /**
    * @brief Ustawia nazwę pliku
    */
    void SetFileName(std::string filename);
    /**
    * @brief Zwraca nazwę pliku
    * @return nazwa pliku
    */
    std::string GetFileName();

    /**
    * @brief Ustawia szerokość klatek
    */
    void SetResolutionWidth(unsigned int width);
    /**
    * @brief Zwraca szerokość klatek
    * @return szerokość klatek
    */
    unsigned int GetResolutionWidth();

    /**
    * @brief Ustawia wysokość klatek
    */
    void SetResolutionHeight(unsigned int height);

    /**
    * @brief Zwraca wysokość klatek
    * @return wysokość klatek
    */
    unsigned int GetResolutionHeight();
    /**
    * @brief Ustawia używany kodek
    */
    void SetCodec(std::string codec);
    /**
    * @brief Zwraca kodek
    * @return kodek
    */
    std::string GetCodec();

    /**
    * @brief Ustawia ilość klatek na sekundę
    */
    void SetFPS(unsigned int fps);

    /**
    * @brief Zwraca ilość klatek na sekundę
    * @return fps
    */
    unsigned int GetFPS();
};

#endif // VIDEO_H
