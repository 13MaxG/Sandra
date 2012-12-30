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
    repository.Register("radius", &r);
    repository.Register("hole", &hole);
}

void Mandelbrot::Before()
{

}

void Mandelbrot::After()
{

}

void Mandelbrot::DrawFrame(cv::Mat frame)
{
    // złap zmienne
    double pointX = px.Get(), pointY = py.Get(); // środek obszaru obserwowanego
    double scale = s.Get();

    // Proporcja obrazu
    double frameRatio = (double)width / (double)height;

    // Szerokość i wysokość obserwowanego fragmentu układu współrzędnych x = Re, y = Im
    // nie, niepamiętma dlaczego akurat C...
    double cwidth = 0, cheight = 0;

    // !!!
    // To scale jest jakieś dziwne, szczególnie w przypadku oddalania w wideo
    cwidth = 3.0 / scale;
    cheight =  cwidth / frameRatio;

    // Punkty graniczne układu tworzące prostokąt
    double minRe, maxRe;
    double minIm, maxIm;

    minRe = pointX - cwidth / 2.0;
    maxRe = pointX + cwidth / 2.0;

    minIm = pointY - cheight / 2.0;
    maxIm = pointY + cheight / 2.0;


    // iter
    unsigned int maxIterations = max_iter.Get();


    double radius = r.Get();





    Argument<double> color_r = c_r;
    Argument<double> color_g = c_g;
    Argument<double> color_b = c_b;

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();

    // Czy dziura ma być czarna?
    bool black_hole = hole;

    // Jedna z delt, zobacz do czego niżej
    double dt =  1.0 / (double)maxIterations;

    // Lecimy dla każdeo punktu z klatki
    for(unsigned int y = 0; y < height; ++y)
    {
        double cIm = maxIm - (double)y*(double)(  (maxIm-minIm)/(height-1) );

        for(unsigned int x = 0; x < width; ++x)
        {
            double cRe = minRe + (double)x*(double)  (  (maxRe-minRe)/(width-1) );
            // Zmienna zespolona c, pozycja (x, y) w układzie współrzednych (Re, Im)

            //  Z, to dopiero prawdziwe wariacje
            double zRe = cRe;
            double zIm = cIm;


            bool inside = true;

            // nnn to niezykła zmienna, albo raczej jej nazwa
            // Mimo tego że jest kompletnie bez sensu, tak zapadła mi w głowie, że nie ma sansu zmieniać jej nazwy
            // A oznacza tyle, ile było iteracji przez zakończeniem iterowania
            unsigned int nnn=  0;

            double abs2 = 0;// = sqrt( zRe*zRe + zIm*zIm );

            // hmmm...
            //double m = std::exp(-1.0 * sqrt( zRe*zRe + zIm*zIm ) ) ;

            // Procent użytwany do palety z kolorami
            double m = 0;

            for(unsigned int i = 1; i <= maxIterations ; i++)
            {
                nnn = i; // :)

                if(coloring == "linear")
                {
                    color_b.Update(dt);
                    color_g.Update(dt);
                    color_r.Update(dt);
                }



                // Jeden ze starych pomysłów, na wszelki przypadek go zostawię
                //m += std::exp(-1.0 * abs ) ;

                // Z = z^2 + c; Liczę na doublach, bo std::complex jest jakieś dziwne
                double zIm2 = zIm*zIm; // pomocnik
                zIm = 2 * zRe*zIm + cIm;
                zRe = zRe*zRe - zIm2 + cRe;

                // KWADRAT Z PIATORASA! (wartość bezwzględna do kwadratu)
                // cóż za sprytne optymalizacje ;)
                abs2 =  zRe*zRe + zIm*zIm ;

                if(coloring == "logarithmic_sinus")
                if(abs2 > radius * radius) // standardowo ma być w, ale co tam...
                {
                    inside = false;
                    break;

                }

                if(coloring == "linear")
                if( abs2 > 4 /* 2 * 2 */)
                {
                    inside = false;



                    if(coloring == "linear")
                    {

                        frame.data[frame.step*y + frame.channels()* x + 0] = color_b.Get();
                        frame.data[frame.step*y + frame.channels()* x +1] = color_g.Get();
                        frame.data[frame.step*y + frame.channels()* x + 2] = color_r.Get();

                    }

                    break;
                }


            }

            if(coloring == "logarithmic_sinus")
            {
                m = 0.5+ 0.5* sin (  nnn -   (  log2 (  abs2 ) / log2( radius )      ))  ;

                // Prawda że czytelnie wygląda, ale fajne jest
                // Tylko jakiś rewolucjonista wymyślił sobie format  koloru BGR
                frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);
            }

            // Klient bierze w ciemno
            if(black_hole&& inside)
            {
                frame.data[frame.step*y + frame.channels()* x + 0] = 0;
                frame.data[frame.step*y + frame.channels()* x +1] = 0;
                frame.data[frame.step*y + frame.channels()* x + 2] = 0;
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
