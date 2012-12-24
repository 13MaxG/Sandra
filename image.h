#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
/**
 * @brief The Image class
 *
 * Ograniczenie: proszę używać tylko formatu PNG
 */
class Image
{
    unsigned int _width, _height;
    std::string _filename;
    unsigned int _compression;
public:
    Image();

    cv::Mat Frame;

    void Prepare();
    void RenderImage();
    void ClearFrame();

    void SetWidth(unsigned int width);
    unsigned int GetWidth();
    void SetHeight(unsigned int height);
    unsigned int GetHeight();

    void SetFileName(std::string filename);
    std::string GetFileName();

    void SetCompression(unsigned int compression);
    unsigned int GetCompression();

};

#endif // IMAGE_H
