#ifndef KEY_H
#define KEY_H

/**
 * @brief Wartość kluczowa
 *
 * Klasa określająca daną wartość w danym czasie.
 * Do użtku z Argument. Wszelkie inne zastosowania mogą wiązać się z błędami
 * Aby poprawnie działało z Argument, typ T musi mieć przeładowane operatory mnożenia.
 * Operatory porównania(większe, mniejsze) odnoszą się do czasu.
 */
template <typename T>
class Key
{
// publiczne wystarczy
public:
    /// Konstruktor domyślny
    Key();


    /**
     * @brief Konstruktor
     *
     * Ustawia wartości podane w parametrach
     * @param val wartość
     * @param a czas
     */
    Key(T value, double time);


    /// @brief Wartość
    T Value;

    /// @brief Czas
    double Time;

    /**
     * @brief Przeładowanie operatora <
     *
     * Porównuje dwa obeikty Key, zwraca prawdę gdy ten pierwszy ma mniejszy czas
    */
    bool operator< ( Key<T> const &comp) const {return Time < comp.Time;}

    /**
     * @brief Przeładowanie operatora >
     *
     * Porównuje dwa obeikty Key, zwraca prawdę gdy ten pierwszy ma większy czas
    */
    bool operator> ( Key<T> const &comp) const {return Time > comp.Time;}

};

#include "key.cpp"

#endif // KEY_H
