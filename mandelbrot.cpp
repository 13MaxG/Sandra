#include "mandelbrot.h"
#include <complex>

Mandelbrot::Mandelbrot() : System()
{
    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);
    repository.Register("iterations", &max_iter);
    repository.Register("pointX", &px);
    repository.Register("pointY", &py);
    repository.Register("scale", &s);
    repository.Register("coloring", &coloring);
}

void Mandelbrot::Before()
{

}

void Mandelbrot::After()
{

}

void Mandelbrot::DrawFrame(cv::Mat frame)
{
    // Całego mandelbrota trzeba napisać od nowa




    double pointX = px.Get(), pointY = py.Get();
    double scale = s.Get();

    double frameRatio = (double)width / (double)height;

    double cwidth = 0, cheight = 0;

    cwidth = 3.0 * scale;
    cheight =  cwidth / frameRatio;

    double minRe, maxRe;
    double minIm, maxIm;

    minRe = pointX - cwidth / 2.0;
    maxRe = pointX + cwidth / 2.0;

    minIm = pointY - cheight / 2.0;
    maxIm = pointY + cheight / 2.0;


    unsigned int maxIterations = max_iter.Get();

    //std::cout<<"minRe: "<<minRe<<"; maxRe: "<<maxRe<<std::endl;
    //std::cout<<"minIm: "<<minIm<<"; maxIm: "<<maxIm<<std::endl;


    bool classic = false;

    if(coloring == "classic")
        classic = true;


    double xxx = 0;
    for(int y = 0; y < height; ++y)
    {
        double cIm = maxIm - (double)y*(double)(  (maxIm-minIm)/(height-1) );
      //  std::cout<<"Y: "<<cIm<<std::endl;
        for(int x = 0; x < width; ++x)
        {
            Argument<double> color_r = c_r;
            Argument<double> color_g = c_g;
            Argument<double> color_b = c_b;

            color_r.Prepare();
            color_g.Prepare();
            color_b.Prepare();

            double cRe = minRe + (double)x*(double)  (  (maxRe-minRe)/(width-1) );
          // std::cout<<"    X: "<<cRe<<std::endl;

            double zRe = cRe;
            double zIm = cIm;
            bool inside = true;


            double m = std::exp(-1.0 * sqrt( zRe*zRe + zIm*zIm ) ) ;
            for(int i = 1; i <= maxIterations; i++)
            {
                if(classic)
                {
                    color_b.Update(1.0/(double)maxIterations);
                    color_g.Update(1.0/(double)maxIterations);
                    color_r.Update(1.0/(double)maxIterations);
                }



                m += std::exp(-1.0 * sqrt( zRe*zRe + zIm*zIm ) ) ;

             //  std::cout<<"TROLOLO: "<<x<<std::endl;
               double zIm2 = zIm*zIm;
               zIm = 2 * zRe*zIm + cIm;
               zRe = zRe*zRe - zIm2 + cRe;

                if( zRe*zRe + zIm*zIm > 4 )
                {
                    inside = false;



                    if(classic)
                    {

                        frame.data[frame.step*y + frame.channels()* x + 0] = color_b.Get();
                        frame.data[frame.step*y + frame.channels()* x +1] = color_g.Get();
                        frame.data[frame.step*y + frame.channels()* x + 2] = color_r.Get();

                    }

                    break;
                }


            }

            if(!classic)
            {
                m /= (double)maxIterations;

                //m = tan(m)/tan(1);
                //if(xxx < m) xxx = m;
                //std::cout<<"m: "<<m<<std::endl;
                frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);
            }

            if(inside)
            {
                //if(!classic)
                //{
                    frame.data[frame.step*y + frame.channels()* x + 0] = 0;
                    frame.data[frame.step*y + frame.channels()* x +1] = 0;
                    frame.data[frame.step*y + frame.channels()* x + 2] = 0;
                //}


            }
        }
    }
   // std::cout<<"XXX: "<<xxx<<std::endl;


}


//void Mandelbrot::Render(double info)
//{
//    // Do wyświetlania procesu
//    double up = info;
//    double tmp = 0;
//    double total = 0;

//    BeforeRedner();

//    std::cout.precision(2);

//    std::cout<<(total)*100<<"% <=> "<<totalFrames <<" <><> "<<0<<" / "<<totalFrames<<std::endl;

//    // Pętla przez wszytskie klatki
//    for(currentFrames = 0; currentFrames < totalFrames; currentFrames++)
//    {
//        // Wyświetlanie procesu

//        if(tmp >= up)
//        {
//            tmp = 0;
//            std::cout<<std::fixed<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;
//        }


//        // OpiS SCENY

//        Update(delta); // aktualizuj parametry


//        double frameHeight = video.GetResolutionHeight();
//        double frameWidth = video.GetResolutionWidth();

//        double pointX = 0.0, pointY=0.0; //
//        double zoom = 1.0;

//        double width; // Układ współrzednych, cześć rzeczywista
//        double height; // -..- część urojona



////        if(frameWidth > frameHeight)
////        {
////            height = 2.0  / zoom;
////            width = (frameWidth / frameHeight) * height;
////        } else
////        {
////            width = 3.5  / zoom;
////            height = (frameHeight / frameWidth) * width;
////        }




//        /*

//        double MinRe = -2.0;
//        double MaxRe = 1.0;
//        double MinIm = -1.2;
//        double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
//        double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
//        double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);


//        unsigned MaxIterations = iterations.Get();

//        for(unsigned y=0; y<ImageHeight; ++y)
//        {
//            double c_im = MaxIm - y*Im_factor;
//            for(unsigned x=0; x<ImageWidth; ++x)
//            {
//                double c_re = MinRe + x*Re_factor;

//                double Z_re = c_re, Z_im = c_im;
//                bool isInside = true;
//                double per = 0;
//                for(unsigned n=0; n<MaxIterations; ++n)
//                {
//                    double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
//                    if(Z_re2 + Z_im2 > 4)
//                    {
//                        isInside = false;

//                        unsigned  char r= 0 , g = 0, b = 0;
//                         per =((double(n))/ ((double)MaxIterations));
//                                            if(per < 0.5)
//                                            {
//                                                r = ((per  / 0.5) * 255.0) ;
//                                                g = 0;
//                                                b = 0;
//                                            } else
//                                            {
//                                                r = 255;
//                                                g = (((per-0.5)/ 0.5) * 255.0) ;;
//                                               b = (((per-0.5)/ 0.5) * 255.0) ;;
//                                            }
//                                          //  data[A.step*i + A.channels()*j + 0]
//                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 0] = b;
//                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x +1] = g;
//                                            video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 2] = r;
//                                            // cv::rectangle( video.Frame, cv::Point(x, y), cv::Point(x+1, y+1), cv::Scalar(b, g, r), 0,);

//                        break;
//                    }
//                    Z_im = 2*Z_re*Z_im + c_im;
//                    Z_re = Z_re2 - Z_im2 + c_re;
//                }
//                if(isInside)
//                {
//                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 0] = 0;
//                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x +1] = 0;
//                    video.Frame.data[video.Frame.step*y + video.Frame.channels()* x + 2] = 0;
//                    //cv::rectangle( video.Frame, cv::Point(x, y), cv::Point(x+1, y+1), cv::Scalar(255, 255, 0), 1);
//                    //cv::cvSet2D(video.Frame, x, y, cv::Scalar(255, 255, 255));
//                }
//            }
//        }
//        */


//        // wyrenderuj!
//        video.RenderFrame();

//        tmp += delta;
//        total +=delta;
//    }
//    std::cout<<(total)*100<<"% <=> "<<totalFrames - currentFrames<<" <><> "<<currentFrames<<" / "<<totalFrames<<std::endl;

//    std::cout<<"Ukończono renderowanie"<<std::endl;

//}
