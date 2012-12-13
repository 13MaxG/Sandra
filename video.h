#ifndef VIDEO_H
#define VIDEO_H

/**
 * @brief Klasa operująca na wideo.
 *
 * Pozwala na utworzenie pliku wideo w formacie AVI.
 * Umożliwia na tworzenie kolejnych klatek filmu. Na klatkach można rysować prymitywy.
 */

class Video
{
private:

  std::string _filename;
    unsigned int _width;
    unsigned int _height;
    std::string _coded;
    unsigned int fps;
public:

    /**
    * @brief Konstruktor
    */
    Video();

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
