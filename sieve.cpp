#include "sieve.h"
#include <ctime>

#define _USE_MATH_DEFINES
#include <cmath>

//RandomDouble(min, max)

Sieve::Sieve()
{
    video.automatic_clear_frame = false;
    precise_info = true;

    repository.Register("iterations", &iterations);

    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);

    repository.Register("n", &n);
    repository.Register("random", &random);
    repository.Register("points", &points);
    repository.Register("liczniki", &liczniki);

}

void Sieve::Before()
{
    data = new point[n];

    for(int i = 0; i < n; i++)
    {
        double a;


        a = (double)i / n;
        if(random) a = ( rand()%100)/100.00;
        data[i] = point( (width/2.0) + cos(2.0*M_PI  * a - M_PI/2.0) * (width/2.0), (height/2.0) + sin(2.0*M_PI * a - M_PI/2.0) * (width/2.0));
    }


    //for(int i = 0; i < n; i++) // Rozbiłem na dwie pętle dla czytelności
       // {
       //     Q.x += data[i].x;
       //     Q.y += data[i].y;
       // }
        //Q.x /= (double)n;
        //Q.y /= (double)n;
    Q = data[0];
        B = Q;

    overall = cv::Mat(cv::Size(width, height),CV_8UC3) ;
    cv::rectangle(overall, cv::Point(0,0), cv::Point(width,height), cv::Scalar(0,0, 0),  CV_FILLED, CV_AA) ;

    if(liczniki)
    {
        licznik = new double*[width];
        for(int x = 0 ; x < width; x++)
        {
            licznik[x] = new double[height];
            for(int y = 0; y < height; y++)
            {
                licznik[x][y] = 0;
            }
        }
    }


}

void Sieve::After()
{

}


void Sieve::DrawFrame(cv::Mat frame)
{

    Argument<double> color_r = c_r;
    Argument<double> color_g = c_g;
    Argument<double> color_b = c_b;

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();

    WriteProcessInfo();




    for(int i = 0; i < ceil((double)iterations / totalFrames); i++)
    {
        double r, g, b;
        r = c_r.GetAbsolute( (double)currentFrame / totalFrames );
        g = c_g.GetAbsolute( (double)currentFrame / totalFrames );
        b = c_b.GetAbsolute( (double)currentFrame / totalFrames );

        // Rysuję
        if(points)
        {
            if(liczniki)
            {
                licznik[(int)round(Q.x)][(int)round(Q.y)] ++;
                if(maks < licznik[(int)round(Q.x)][(int)round(Q.y)]) maks = licznik[(int)round(Q.x)][(int)round(Q.y)];
            } else
            {
                frame.data[overall.step*(int)round(Q.y) + overall.channels()*(int)round(Q.x) + 0] = b;
                frame.data[overall.step*(int)round(Q.y) + overall.channels()* (int)round(Q.x) + 1] = g;
                frame.data[overall.step*(int)round(Q.y) + overall.channels()* (int)round(Q.x) + 2] = r;
            }
        } else
        {
            cv::line(overall, cv::Point(Q.x,Q.y), cv::Point(B.x,B.y), cv::Scalar(b,g,r), 1, CV_AA);
            B = Q;
        }

        // Obliczam nowe współrzędnie
        int s = rand()%n;
        Q.x = (Q.x + data[s].x)/2.0;
        Q.y = (Q.y + data[s].y)/2.0;




   }
    if(liczniki)
    {
        for(int y = 0; y < height; ++y)
            {
                for(int x = 0; x < width; ++x)
                {
               frame.data[frame.step*y + frame.channels()* x + 0] = c_b.GetAbsolute((double)licznik[x][y]/maks);
                 frame.data[frame.step*y + frame.channels()* x + 1] = c_g.GetAbsolute((double)licznik[x][y]/maks);
                   frame.data[frame.step*y + frame.channels()* x + 2] = c_r.GetAbsolute((double)licznik[x][y]/maks);
                }
        }

    } else
    if(points)
    {
        frame = overall;
    } else
    {
    for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {


                frame.data[frame.step*y + frame.channels()* x + 0] = overall.data[frame.step*y + overall.channels()* x + 0];
                frame.data[frame.step*y + frame.channels()* x + 1] = overall.data[frame.step*y + overall.channels()* x + 1];
                frame.data[frame.step*y + frame.channels()* x + 2] = overall.data[frame.step*y + overall.channels()* x + 2];


            }
        }
    }

}
