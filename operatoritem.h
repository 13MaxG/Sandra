#ifndef OPERATORITEM_H
#define OPERATORITEM_H

#include <string>


template <typename T>
class OperatorItem
{
public:
    OperatorItem();
    OperatorItem(T* o, std::string n);
    T* object;
    std::string name;
};

#include "operatoritem.cpp"

#endif // OPERATORITEM_H
