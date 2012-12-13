#ifndef KEY_CPP
#define KEY_CPP

#include "key.h"

template <typename T>
Key<T>::Key()
{
    Time = 0;
}

template <typename T>
Key<T>::Key(T value, double time)
{
    Value = value;
    Time = time;
}

#endif // KEY_CPP
