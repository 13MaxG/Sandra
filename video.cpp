#include "video.h"

Video::Video()
{
    Restart();
    _writer = cv::VideoWriter();
}

void Video::Restart()
{
    _lock = false;
    SetFileName("video.avi");
    SetResolutionWidth(1280);
    SetResolutionHeight(720);
    SetFPS(30);
    ClearFrame();

}

void Video::Prepare()
{
    _lock = true;
        //CV_FOURCC('D', 'I', 'V', 'X')
       // CV_FOURCC('D', 'I', 'B', ' ')
    //CV_FOURCC('i','Y', 'U', 'V')
    //CV_FOURCC('I','Y', 'U', 'V')
    //I420  CV_FOURCC('I','4', '2', '0')
    _writer.open(GetFileName() , CV_FOURCC('I','4', '2', '0') , GetFPS(), cv::Size(GetResolutionWidth(), GetResolutionHeight()), true);//open(GetFileName(), CV_FOURCC( GetCodec()[0], GetCodec()[1], GetCodec()[2], GetCodec()[3]), GetFPS(), cv::Size(GetResolutionWidth(), GetResolutionWidth()), true );
    Frame = cv::Mat(cv::Size(GetResolutionWidth(), GetResolutionHeight()),CV_8UC3) ;

}

void Video::ClearFrame()
{
    // Stare
    //delete Frame;
    //Frame =  new cv::Mat(cv::Size(1920, 1080),CV_8UC3) ;

    //Czarne tło; Wiem że PRYMITYWnie, ale nie mam lepszeo pomysłu
    cv::rectangle(Frame, cv::Point(0,0), cv::Point(GetResolutionWidth(),GetResolutionHeight()), cv::Scalar(0,0, 0),  CV_FILLED, CV_AA) ;
}

void Video::RenderFrame()
{
    _writer << Frame;
    ClearFrame();
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
