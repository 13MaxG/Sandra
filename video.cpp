#include "video.h"

Video::Video()
{
    automatic_clear_frame = true;
    Restart();
    _writer = cv::VideoWriter();
}

void Video::Restart()
{
    // wypadki chodzą po użytkownikach
    _lock = false;
    SetFileName("video.avi");
    SetCodec("DIVX");
    SetResolutionWidth(1280);
    SetResolutionHeight(720);
    SetFPS(30);
    ClearFrame();
}

void Video::Prepare()
{
    _lock = true; // nawet blokada jest

    // Zainicjuj plik z wideo
    _writer.open(GetFileName() , CV_FOURCC(GetCodec()[0], GetCodec()[1], GetCodec()[2], GetCodec()[3]) , GetFPS(), cv::Size(GetResolutionWidth(), GetResolutionHeight()), true);//open(GetFileName(), CV_FOURCC( GetCodec()[0], GetCodec()[1], GetCodec()[2], GetCodec()[3]), GetFPS(), cv::Size(GetResolutionWidth(), GetResolutionWidth()), true );
    // i stwórz pierwszą klatkę(nie, nie na chochliki)
    Frame = cv::Mat(cv::Size(GetResolutionWidth(), GetResolutionHeight()),CV_8UC3) ;

}

void Video::ClearFrame()
{
    //Czarne tło; Wiem że PRYMITYWnie, ale nie mam lepszeo pomysłu
    cv::rectangle(Frame, cv::Point(0,0), cv::Point(GetResolutionWidth(),GetResolutionHeight()), cv::Scalar(0,0, 0),  CV_FILLED, CV_AA) ;
}

void Video::RenderFrame()
{
    // I za to podoba mi się I/O z OpenCV
    _writer << Frame;
    if(automatic_clear_frame) ClearFrame();
}

bool Video::IsLocked()
{
    return _lock;
}

void Video::SetFileName(std::string filename)
{
    if(!_lock) _filename = filename;
}

std::string Video::GetFileName()
{
    return _filename;
}

void Video::SetResolutionWidth(unsigned int width)
{
    if(!_lock) _width = width;
}

unsigned int Video::GetResolutionWidth()
{
    return _width;
}

void Video::SetResolutionHeight(unsigned int height)
{
    if(!_lock) _height = height;
}

unsigned int Video::GetResolutionHeight()
{
    return _height;
}


void Video::SetFPS(unsigned int fps)
{
    if(!_lock) _fps = fps;
}

unsigned int Video::GetFPS()
{
    return _fps;
}

void Video::SetCodec(std::string codec)
{
   _codec = codec;
}

std::string Video::GetCodec()
{
    return _codec;
}

