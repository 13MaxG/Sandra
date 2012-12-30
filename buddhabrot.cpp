#include "buddhabrot.h"
#include "random.h"
#include <complex>


Buddhabrot::Buddhabrot() : System()
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
    repository.Register("points", &calc_points);
}

void Buddhabrot::Before()
{

}

void Buddhabrot::After()
{

}

void Buddhabrot::DrawFrame(cv::Mat frame)
{
    // Całego Buddhabrota trzeba napisać od nowa




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

    double radius = r.Get();

    if(coloring == "classic")
        classic = true;

    bool black_hole = true;

    double xxx = 0;

     int points = calc_points.Get();//;50000000
     // radius = 2;


     double odl_x = (maxRe - minRe) / width;
     double odl_y = (maxIm - minIm) / height;


     double **licznik = new double*[width];
     for(int x = 0 ; x < width; x++)
     {
         licznik[x] = new double[height];
         for(int y = 0; y < height; y++)
         {
             licznik[x][y] = 0;
         }
     }

     double * offRe = new double[maxIterations];
     double * offIm = new double[maxIterations];

     int coal = 0;
     int koks = 10000;
    for(int po = 0; po < points; po++)
    {
        coal++;
        if(coal >  koks)
        {
            std::cout<<(double)po/(double)points*100<<" %"<<std::endl;
            coal = 0;
        }
        double pRe = RandomDouble(minRe, maxRe);
        double pIm = RandomDouble(minIm, maxIm);

         double cIm = pIm;//maxIm - (double)y*(double)(  (maxIm-minIm)/(height-1) );
         double cRe = pRe;//minRe + (double)x*(double)  (  (maxRe-minRe)/(width-1) );

         double zRe = 0;
         double zIm = 0;

         double abs2;
         bool hop = true;



         int nnn = 0;
         for(int i = 0; i < maxIterations ; i++)
         {
             nnn = i;

             // normalnie
             double zIm2 = zIm*zIm;
             zIm = 2 * zRe*zIm + cIm;
             zRe = zRe*zRe - zIm2 + cRe;

             //abs = sqrt( zRe*zRe + zIm*zIm );
             abs2 = zRe*zRe + zIm*zIm ;

             offRe[i] = zRe;
             offIm[i] = zIm;

             if(abs2 > radius*radius) //4
             {
                 hop = false;
                 break;
             }
         }

          double *tmpx = new double;
          double *tmpy = new double;

        if(hop == false)
        {
            for(int i = 0; i < nnn; i++)
            {

                double x = offRe[i];
                double y = offIm[i];

                int xx, yy;

                modf((x - minRe) / odl_x , tmpx);

                xx = (*tmpx) ;

                modf((y - minIm) / odl_y, tmpy);
                yy = (*tmpy) ;
               // std::cout<<"#       SONDA( "<<*tmpx<<", "<<*tmpy<<");"<<std::endl;
                double errorx = (x - minRe) / odl_x - xx;
                double errory = (y - minIm) / odl_y - yy;
//log2( (licznik[x][y] - mini) / (maxi - mini)) ;
                //std::cout<<"SONDA( "<<xx<<", "<<yy<<");"<<std::endl;
                if(xx < width && yy < height)
                    licznik[xx][yy] +=  ( ( 1 - errorx) * (1 - errory))   ;
                if(xx +1< width && yy < height)
                    licznik[xx+1][yy] += ( ( 1 - errorx) * (errory));
                if(xx < width && yy+1 < height)
                    licznik[xx][yy+1] += ( (  errorx) * (1 - errory));
                if(xx + 1 < width && yy + 1< height)
                    licznik[xx+1][yy+1] += (  (  errorx) * ( errory));

             //   licznik[xx][yy] = log2( licznik[xx][yy]) / log2(i+2);
              //  licznik[xx+1][yy] = log2( licznik[xx+1][yy]) / log2(i+2);
               // licznik[xx][yy+1] = log2( licznik[xx][yy+1]) / log2(i+2);
               // licznik[xx+1][yy+1] = log2( licznik[xx+1][yy+1]) / log2(i+2);
            }

        }

    }
    //std::cout<<"cześć 2."; int kro= 0;
   // std::cin>>kro;

    long double  maxi = 0, mini= 0, sumi = 0;
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if(licznik[x][y] < mini)
                mini = licznik[x][y];
            if(licznik[x][y] > maxi)
                maxi = licznik[x][y];
            sumi += licznik[x][y];
        }
    }
    sumi /= height * width; // śrendia




//    Argument<double> color_r ;
//    Argument<double> color_g ;
//    Argument<double> color_b;

//    for(int i = 0; i < 100 ;i++)
//    {
//        double p = (double) i / 100.0;
//        color_r.Set(Key<double>( 255.0 * p, p));
//        color_g.Set(Key<double>( 255.0 * p , p));
//        color_b.Set(Key<double>( 255.0*log(p) / log(100), p));
//    }


        Argument<double> color_r ;// = c_r;
        Argument<double> color_g ;// = c_g;
        Argument<double> color_b  ;//= c_b;

        unsigned int color_level_num = 100;
        for(unsigned int i = 0 ; i <= color_level_num; i++)
        {
            double p = (double) i / (double) color_level_num;


            //color_r.Set(Key<double>( c_r.GetAbsolute(p) *   log(i) / log(color_level_num), p ));
            //color_g.Set(Key<double>( c_g.GetAbsolute(p) *    log(i) / log(color_level_num), p ));
            //color_b.Set(Key<double>( c_b.GetAbsolute(p) *    log(i) / log(color_level_num) , p ));



// TO JEST BARADZO WAŻNE
             color_r.Set(Key<double>( 255.0 *   p, p ));
            color_g.Set(Key<double>( 255.0 *    p, p ));
            color_b.Set(Key<double>( 255.0 *    log(i) / log(color_level_num) , p ));

        }

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();



    std::cout<<mini<<" > "<<maxi<<std::endl;
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {



               //abs = licznik;



              //  m =0.5+ 0.5* sin (  nnn -   (  log2 (  abs ) / log2(radius)      ))  ;
                 //m =0.5+ 0.5* sin (  nnn - log (  abs )  );




            // !!! 2 *
            double m = 2 * (licznik[x][y]-mini) / (maxi - mini);





           /*
            double m = 0;
            if(licznik[x][y] < sumi)
            {
                m = (licznik[x][y]-mini) / (sumi - mini);
            } else
            {
                 m = (licznik[x][y]-sumi) / (maxi - sumi);
            }
                */


            //
           // std::cout<<"SONDA( "<<x<<", "<<y<<") = "<<m<<std::endl;
                 frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                 frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                 frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);

        }
    }
   // std::cout<<"XXX: "<<xxx<<std::endl;


}
