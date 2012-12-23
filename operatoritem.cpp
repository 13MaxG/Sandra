#ifndef OPERATORITEM_CPP
#define OPERATORITEM_CPP

#include "operatoritem.h"

template <typename T>
OperatorItem<T>::OperatorItem()
{
}
template <typename T>
OperatorItem<T>::OperatorItem(T *o, std::string n)
{
    object = o;
    name = n;
}

#endif //OPERATORITEM_CPP
