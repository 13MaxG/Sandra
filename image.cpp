#include "image.h"
#include <iostream>

Image::Image()
{
    _filename = "image.png";
    _compression = 3;
    _width = 800;
    _height = 600;
}

void Image::ClearFrame()
{
    cv::rectangle(Frame, cv::Point(0,0), cv::Point(GetWidth(),GetHeight()), cv::Scalar(0,0, 0),  CV_FILLED, CV_AA) ;

}

void Image::Prepare()
{
    Frame = cv::Mat(cv::Size(GetWidth(), GetHeight()),CV_8UC3) ;
    ClearFrame();
}

void Image::RenderImage()
{
    std::vector<int> p;
    p.push_back(CV_IMWRITE_PNG_COMPRESSION);
    p.push_back(GetCompression());

    std::cout<<"!"<<std::endl;
    cv::imwrite(GetFileName(), Frame, p);
}


void Image::SetWidth(unsigned int width)
{
    _width = width;
}

unsigned int Image::GetWidth()
{
    return _width;
}

void Image::SetHeight(unsigned int height)
{
    _height = height;
}

unsigned int Image::GetHeight()
{
    return _height;
}

void Image::SetFileName(std::string filename)
{
    _filename = filename;
}

std::string Image::GetFileName()
{
    return _filename;
}

void Image::SetCompression(unsigned int compression)
{
    _compression = compression;
}

unsigned int Image::GetCompression()
{
    return _compression;
}

