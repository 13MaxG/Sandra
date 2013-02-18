#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <list>
#include <algorithm>
#include "key.h"

/**
 * @brief Argument
 *
 * Argument umożliwa płynne zmienianie się wartości w czasie. Wartości są przetrzymywane w liście( data).
 * Na każdą wartość przypada również moment czasu w kórym ma być akywna. Gdy aktualny czas będzie
 * gdzieś pośrodku, wartość będzie proporcjonalna.
 *
 * Czas jest liczony od 0.0 do 1.0 (double), przy czym 0 to początek a 1 to koniec.
 * Wartości dodane do listy zostaną odpowiednio posortowane(dzięki metodzie Prepare ).
 * W przypadku złożonych konfiuracji proszę dbać o to, aby w liście wstąpił element o czasie 0.0(począkowy)
 * i 1.0 (końcowy). Podawanie czasu z zakresu <0, 1> może spowodować błędy. Nie zalecane jest dodawanie
 * kilku wartości o identycznych czasach.
 *
 * Czas początkowy to 0.0. Argment metody Update zwiększa czas o podany argument, a następnie oblicza dla
 * niego aktualną wartość.
 *
 * Typ musi mieć przeładowane arumenty porównania(<, >) oraz mnożenia(*)
 *
 * Uwaga: Wymagane jest aby lista posiadał conajmniej jeden element!
 */
template <typename T>
class Argument
{
private:
    /**
     * @brief Lista z kluczowymi wartościami w czasie
     */
    std::list< Key<T> > data;

    /**
     * @brief Element w liście po aktualnym
     */
    typename std::list < Key<T> >::iterator prev;

    /**
     * @brief Element w liście przed aktualnym
     */
    typename std::list < Key<T> >::iterator next;

    /**
     * @brief Aktualny czas i wartość zmiennej
     */
    Key<T> current;

public:
    /**
     * @brief Konstruktor
     */
    Argument();

    /**
     * @brief Przygotowuje do działania
    */
    void Prepare();

    /**
     * @brief Aualtualnia wartość zmiennej
     *
     * Metoda zwiększa aktualny czas o up, a nasępnie oblicza nową wartość zmiennej.
     * @param up czas o jaki nastąpił postęp
     */
    void Update(double up);

    /**
     * @brief Ustawia kluczową wartość zmiennym w danym czasie
     *
     * UWAGA: Aby korzystać z Update() najpierw przygotuj za pomocą Prepare()
     *
     * @param key Wartość i czas
     */
    void Set(Key<T> key);

    /**
     * @brief Zwraca aktualną wartość zmiennej
     */
    T Get();

    /**
     * @brief Zwraca wartość w danym procencie płnnej zmiany. Nie stosować w pętlach, szczególnie dla Video. Dla Video jest zwykłe Get, a to jes dla Picture
     * @param at procent płynnej zmiany
     *
     * Duża część kodu wspólnego z Update.
    */
    T GetAbsolute(double at);

    /**
     * @brief Zwraca aktualny czas
     */
    double GetTime();


    /**
     * @brief Zwraca czas następnej wartości kluczowej
     * Normalnie nie będzie potrzebne. Dozwolone do użytku tylko w krytycznych stuacjach.
     *
     * @return  czas następnego
     */
    double GetNextTime();

    /**
     * @brief Skacze do następnego elementu
     *
     * Normalnie nie będzie potrzebne. Dozwolone do użytku tylko w krytycznych stuacjach.
     *
     * @return czy koniec
     */
    bool JumpToNext();


    /// pomocnik, czy dostarłem na koniec
    bool IsEnd;
};

#include "argument.cpp"

#endif // ARGUMENT_H
