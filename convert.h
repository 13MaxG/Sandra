#ifndef CONVERT_H
#define CONVERT_H

#include <sstream>
#include <ctime>

// Funkcje konwertujące obiekty w ciągi znaków i ciągi znaków w obiekty
// Potrzebne do wczytywania konfiguracji


template<typename T>
std::string toString(T var)
{
    std::ostringstream ss;
    ss << var;
    return ss.str();
}

template<typename T>
T fromString(std::string str)
{
    T var;
    std::istringstream iss(str);
    iss >> var;

    return var;
}




#endif // CONVERT_H
