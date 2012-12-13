#include "system.h"
#include <iostream>

System::System()
{
    x.Set(Key<double>(0.0, 0.0));
    x.Set(Key<double>(361.0, 0.2));
    x.Set(Key<double>(400.0, 0.5));
    x.Set(Key<double>(653.0, 0.6));
    x.Set(Key<double>(0.0, 1.0));
    x.Prepare();

    y.Set(Key<double>(0.0, 0.0));
    y.Set(Key<double>(213.0, 0.1));
    y.Set(Key<double>(400.0, 0.4));
    y.Set(Key<double>(50.0, 0.8));
    y.Set(Key<double>(600.0, 1.0));
    y.Prepare();

    r.Set(Key<double>(0, 0.0));
    r.Set(Key<double>(250.0*0.618, 0.618));
    r.Set(Key<double>(250, 1.0));
    r.Prepare();
}

void System::Update()
{
    x.Update(0.01);
    y.Update(0.01);
    r.Update(0.01);
}

void System::Render()
{
    video.Prepare();

    for(int i = 0; i < 100; i++)
    {
        Update();
        cv::line(video.Frame, cv::Point(video.GetResolutionWidth()/2.0, video.GetResolutionHeight()/2.0), cv::Point(x.Get(),y.Get()), cv::Scalar(r.Get(), 225, 235), 1, CV_AA);

        video.RenderFrame();
    }

}
