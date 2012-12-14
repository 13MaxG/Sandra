#include "lissajous.h"

Lissajous::Lissajous() : System()
{
    delta = 0;
    spiral = false;
}

void Lissajous::Load(char* fileName)
{
    file.open(fileName, std::ios::in);

    std::string line;
    Command command;

    int i = 0;
    while(true)
    {
        i++;
        std::getline(file, line);
        if(file.eof()) break;

        command.Analize(line, i);

                if(!command.isOk()) continue;

        // Ważny moment!

// Dotyczące wideo

        // Nazwa pliku
        if(command.Name() == "video_file_name")
        {
            if(command.NumbersOfArgument() == 1)
            {
                video.SetFileName(command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        // Szerokość klatki
        if(command.Name() == "video_resolution_width")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetResolutionWidth(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        // Wysokość klatki
        if(command.Name() == "video_resolution_height")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetResolutionHeight(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        // Ilość klatek na sekundę
        if(command.Name() == "video_fps")
        {
            if(command.NumbersOfArgument() == 1)
            {

                video.SetFPS(fromString< unsigned int > (command[0]));
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        // Czas trwania
        if(command.Name() == "duration_time")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalTime = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        // czas trwania w klatkach
        if(command.Name() == "duration_frames")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalFrames = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "duration_frames")
        {
            if(command.NumbersOfArgument() == 1)
            {

                totalFrames = fromString< unsigned int > (command[0]);
            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
/////////
        if(command.Name() == "radius_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                radius.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "scale_x_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                scale_x.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "scale_y_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                scale_y.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "factor_x_cos_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                factor_x_cos.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }else
        if(command.Name() == "factor_y_sin_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                factor_y_sin.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }  else
        if(command.Name() == "jump_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                jump.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "precision_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                precision.Set(Key<unsigned int>(fromString< unsigned int > (command[0]), fromString< unsigned int > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "jumps_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                jumps.Set(Key<unsigned int>(fromString< unsigned int > (command[0]), fromString< unsigned int > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "color_r_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_r.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "color_g_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_g.Set(Key<double>(fromString< double> (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        } else
        if(command.Name() == "color_b_add")
        {
            if(command.NumbersOfArgument() == 2)
            {

                color_b.Set(Key<double>(fromString< double > (command[0]), fromString< double > (command[1])));

            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }else
        if(command.Name() == "set_spiral")
        {
            if(command.NumbersOfArgument() == 1)
            {
                 spiral = command[0] == "true";


            } else
                std::cout<<"("<<i<<"): Błąd: niepoprawna ilość argumentów dla teo polecenia"<<std::endl;

        }
/////////
// Brak
        else
        {

            std::cout<<"("<<i<<"): Błąd: nie znaleziono polecenia"<<std::endl;
        }

    }

    file.close();
}

void Lissajous::Update()
{
    radius.Update(delta);
    scale_x.Update(delta);
    scale_y.Update(delta);
    factor_x_cos.Update(delta);
    factor_y_sin.Update(delta);
    jump.Update(delta);
    precision.Update(delta);
    jumps.Update(delta);
    color_r.Update(delta);
    color_g.Update(delta);
    color_b.Update(delta);
}

void Lissajous::Render()
{
    // Policz ostatnie rzeczy
    if(totalTime != 0)
    {
        totalFrames = video.GetFPS() * totalTime;

    }
    delta = 1.0 / totalFrames;



    // Przygotuj argumenty
    radius.Prepare();
    scale_x.Prepare();
    scale_y.Prepare();
    factor_x_cos.Prepare();
    factor_y_sin.Prepare();
    jump.Prepare();
    precision.Prepare();
    jumps.Prepare();
    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();

    // Przygotuj wideo
    video.Prepare();

    for(currentFrames = 0; currentFrames < totalFrames; currentFrames++)
    {
        Update();

        Argument<double> color_r2 = color_r;
        Argument<double> color_g2 = color_g;
        Argument<double> color_b2 = color_b;

        color_r2.Prepare();
        color_g2.Prepare();
        color_b2.Prepare();
        double d2 = 1.0 / precision.Get();

        //
        double alpha = 0;
        double dAlpha = 2.0 * M_PI / precision.Get();

        double x = 0, y = 0;
        double x0 = 0, y0 = 0;


        double r;
        double rr = radius.Get();

        if(spiral) r = 0; else r = rr;



        for(int j = 0; j < jumps.Get(); j++)
        for(int i = 0; i < precision.Get(); i++)
        {
            x0 = x;
            y0 = y;
            alpha += dAlpha;

            color_r2.Update(d2);
            color_g2.Update(d2);
            color_b2.Update(d2);

            if(spiral) r += jump.Get() / precision.Get() * rr;

            x = (video.GetResolutionWidth()/2)
                    + r * scale_x.Get() * cos(alpha * factor_x_cos.Get());
            y = (video.GetResolutionHeight()/2)
                    + r * scale_y.Get() * sin(alpha * factor_y_sin.Get());
            //cv::line(video.Frame, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(127, 0, 127), 1, CV_AA);



            if(i>0 || j != 0 )
            cv::line(
                video.Frame,
                cv::Point(x0, y0),
                cv::Point(x,y),
                cv::Scalar(color_b2.Get(), color_g2.Get(), color_r2.Get()),
                1,
                CV_AA);


        }

        video.RenderFrame();
    }


}
