#ifndef COMMAND_H
#define COMMAND_H

#include <string>

/**
 * @brief Klasa wyłuskująca informacje o poleceniu
 *
 * Wyłuskuje z polecenia:
 *      - nazwę
 *      - ilość parametrów
 *      - parametry
 * Nazwę można pobrać za pomocą Name()
 * Ilość parametrów można pobrać za pomocą NumbersOfArument();
 * Parametry są do odbioru poprzez operator [] lub funkcję Get().
 *
 * W znakach { i } można umieszczać komentarze
 * Jeżeli pierwszym znakiem polecenia będzie # to polecenie zostanie poraktowane jak komentarz
 *
 * Białe znaki są usuwane o ile nie znajdują się przed owarciem nawiasu. Są wtedy wliczane do nazwy.
 *
 * Jeżeli zostaną zauważone jakieś błędy, lub polecenie jest komentarzem(na początku #), metoda isOk() zwróci fałsz.
 *
 * To co znajduje się po zakończeniu ");" jest traktowane jak komentarz
 *
 * Budowa polecenia:
 * _NAZWA_POLECENIA(ARGUMENT_1, {komentarzyk}ARGUMENT_2, ...);
 * # nie jest ważne co tu wpiszę, program i tak to pominie
 *
 * TODO:
 *  - pomiń usuwanie białch znaków z arumentów jeżeli znajdują się w cudzysłowach
 */
class Command
{
    /**
     * @brief Czy wszytsztko poszło ok?
     */
    bool _ok;

    /**
     * @brief Nazwa polecenia
     */
    std::string _name;
    /**
     * @brief Dynamiczna tablica z argumentami
     */
    std::string *_arguments;
    /**
     * @brief Ilość arumentów
     */
    unsigned int _number_of_argument;

public:

    Command();

    /**
     * @brief Konstruktor
     *
     *  Zobacz Analize()
     *
     * @param command Polecenia
     * @param line Numer lini polecenia (opcjonalnie)
     */
    Command(std::string command, unsigned int line);

    /**
     * @brief Analizuje podane polecenie
     *
     * Usuwa białe znaki z argumentów. Usuwa komentarze. Liczy ilość arumentów.
     * Wyłuskuje nazwe i arumenty.
     * Argument może line pomocny przy debugowaniu
     *
     * @param command Polecenia
     * @param line Numer lini polecenia (opcjonalnie)
     */
    void Analize(std::string command, unsigned int line);

    /**
     * @brief Zwraca nazwę polecenia
     */
    std::string Name();
    /**
     * @brief Zwraca argumentu
     * @param arg indekst argumentu
     */
    std::string Get(unsigned int arg);
    /**
     * @brief Zwraca ilość arumentów
     */
    unsigned int NumbersOfArgument();
    /**
     * @brief Czy z wszytko wporządku?
     */
    bool isOk();

    /**
     * @brief Zapewnia dostęp do parametrów poprzed operator [].
     * @param arg indek parametru
     */
    std::string  operator[](unsigned int arg) {return Get(arg);}
};

#endif // COMMAND_H
