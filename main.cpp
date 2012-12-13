#include <iostream>

#include "video.h"
#include "argument.h"

using namespace std;

int main()
{
    Video video;
    video.Prepare();

    int x = 0;
        while( true) //Show the image captured in the window and repeat
        {
            x ++;
            if(x>120) break;

            cv::circle(video.Frame, cv::Point(300,300), x,  cv::Scalar(255, 255, 255), 1, CV_AA);

            cv::rectangle(video.Frame, cv::Point(288,105), cv::Point(288+2*x,105+3*x), cv::Scalar((x+50)%255,(x)%255, (x+100)%255),  2, CV_AA) ;

            video.RenderFrame();
        }

    return 0;
}

