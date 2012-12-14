#ifndef ARGUMENT_CPP
#define ARGUMENT_CPP

#include "argument.h"
#include <iostream>
#include <cmath>

template <typename T>
Argument<T>::Argument()
{
    current.Time = 0; // Dla bezpieczeństwa
}


template<typename T>
void Argument<T>::Prepare()
{
    current.Time = 0; // Dla bezpieczeństwa
    data.sort(); // Sortuj listę
    current = *data.begin(); // Aktualny element to pierwszy element
    next = data.begin(); next++; // Następny element to drugi element
    prev = data.begin(); // Poprzedni element to pierwszy element
}

template<typename T>
void Argument<T>::Update(double up)
{

    Key<T> now; // Nowa wartość zmiennej

    now.Time = current.Time + up; // Wylicz nowy czas

    // Złap takie elementy kluczowe aby obejmowały aktualny czas
    // (zwykle wystarczy jeden obieg)
    while(now.Time >= (*next).Time)
    {
        // Skocz do elementów dalszch o jeden
        next++;
        prev++;

        // (zabezpieczenie)
        // Jeżeli element następny uderzy w koniec listy
        // to element poprzedni i następny to ostatni element
        if((next) == data.end())
        {
            next--;
            prev--;
            break;//broke; broken :)
        }
    }

    //(zabezpieczenie)
    // jeżeli jest tylko jeden element
    if(next == data.begin())
    {
        prev = next;
    }

    double per; // Procent przejścia pomiędzy wartościami kluczowymi
    per = (now.Time-(*prev).Time) / ((*next).Time - (*prev).Time);

    //(zabezpieczenie) zadbaj o przypadki graniczne
    if(per > 1.0) per = 1.0;

    // Aktualna wartość
    now.Value  = per * ((*next).Value - (*prev).Value) + (*prev).Value;

    // Gotowe
    current = now;
}

/**
 *  W przypadku szablonu int, zwracana zawartość będzie zaokrąglana roundem, a nie dzielona poprostu divem6t
 */
template<>
inline void Argument<int>::Update(double up)
{

    Key<int> now; // Nowa wartość zmiennej

    now.Time = current.Time + up; // Wylicz nowy czas

    // Złap takie elementy kluczowe aby obejmowały aktualny czas
    // (zwykle wystarczy jeden obieg)
    while(now.Time >= (*next).Time)
    {
        // Skocz do elementów dalszch o jeden
        next++;
        prev++;

        // (zabezpieczenie)
        // Jeżeli element następny uderzy w koniec listy
        // to element poprzedni i następny to ostatni element
        if((next) == data.end())
        {
            next--;
            prev--;
            break;//broke; broken :)
        }
    }

    //(zabezpieczenie)
    // jeżeli jest tylko jeden element
    if(next == data.begin())
    {
        prev = next;
    }

    double per; // Procent przejścia pomiędzy wartościami kluczowymi
    per = (now.Time-(*prev).Time) / ((*next).Time - (*prev).Time);

    //(zabezpieczenie) zadbaj o przypadki graniczne
    if(per > 1.0) per = 1.0;

    // Aktualna wartość
    now.Value  = round( per * ((*next).Value - (*prev).Value) + (*prev).Value );

    // Gotowe
    current = now;
}
/**
 *  W przypadku szablonu unsigned int, zwracana zawartość będzie zaokrąglana roundem, a nie dzielona poprostu divem6t
 */
template<>
inline void Argument<unsigned int>::Update(double up)
{

    Key<unsigned int> now; // Nowa wartość zmiennej

    now.Time = current.Time + up; // Wylicz nowy czas

    // Złap takie elementy kluczowe aby obejmowały aktualny czas
    // (zwykle wystarczy jeden obieg)
    while(now.Time >= (*next).Time)
    {
        // Skocz do elementów dalszch o jeden
        next++;
        prev++;

        // (zabezpieczenie)
        // Jeżeli element następny uderzy w koniec listy
        // to element poprzedni i następny to ostatni element
        if((next) == data.end())
        {
            next--;
            prev--;
            break;//broke; broken :)
        }
    }

    //(zabezpieczenie)
    // jeżeli jest tylko jeden element
    if(next == data.begin())
    {
        prev = next;
    }

    double per; // Procent przejścia pomiędzy wartościami kluczowymi
    per = (now.Time-(*prev).Time) / ((*next).Time - (*prev).Time);

    //(zabezpieczenie) zadbaj o przypadki graniczne
    if(per > 1.0) per = 1.0;

    // Aktualna wartość
    now.Value  = round( per * ((*next).Value - (*prev).Value) + (*prev).Value );

    // Gotowe
    current = now;
}

template<typename T>
void Argument<T>::Set(Key<T> key)
{
    data.push_back(key);
}

template<typename T>
T Argument<T>::Get()
{
    return current.Value;
}

template<typename T>
double Argument<T>::GetTime()
{
    return current.Time;
}

#endif // ARGUMENT_CPP
