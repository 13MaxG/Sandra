#ifndef CONVERT_H
#define CONVERT_H

#include <sstream>

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
