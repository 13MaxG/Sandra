#include "command.h"
#include <queue>
#include <iostream>
#include <cctype> // dla isspace

Command::Command()
{
}

Command::Command(std::string command, unsigned int line = 0)
{
    Analize(command, line);
}

void Command::Analize(std::string command, unsigned int line = 0)
{
    _ok = true; // Jak narazie wszystko wydaje się być w porządku

    // Zobacz czy czasem polecenie nie ma zostać pominięte
    if(command[0] == '#')
    {
        _ok = false;
        return;
    }

    // Usuń komentarze
    size_t tmp = command.find('{'); // od
    while(tmp != std::string::npos) // Jeżeli znalazło coś
    {
        size_t tmp2 = command.find('}', tmp) + 1; // do
        if(tmp2 != std::string::npos) // jeżeli znalazło coś
        {
            command.erase(tmp, tmp2); // usuń
        } else
        {
            // błąd!
            _ok = false;
            // Powiadom że komentarz jest niepełny
            std::cout<<"("<<line<<") Brak zamknęcia komentarzu w: "<<command<<std::endl;
        }
        tmp=command.find("{", tmp+1);
    }



    size_t x; // Numer znaku w którym znajduje się początek nawiasu
    x = command.find("(")+1;

    //wyczyść białe znaki w arumenach
    for(size_t i= x; i < command.size(); i++)
    {

        if(isspace(command[i]) != 0 ) command.erase(i, 1);
    }

    _name = command.substr(0, x-1); // Wyłuskaj nazwę polecenia

    _number_of_argument = 0; // Na początku było... nic nie było?

    size_t e = command.find(");"); // Znajdź koniec

    // jeżeli odległość robi znaczenie, to coś tam musi być!
    if(e - x > 1) _number_of_argument = 1;

    size_t p = command.find(",", x); // Zmienna pomocnicza, OD
    std::queue<size_t> data; // Lista w której trzymane są pozycje przecinków

    while(p != std::string::npos) // Jeżeli znalazło
    {
        _number_of_argument ++; // to znak, że mamy więcej argumentów
        data.push(p); // Zapamiętaj pozycje
        p=command.find(",", p+1); // Hop dalej!
    }

    // Wiemy ile będzie arumentów, to możemy stworzyć tablicę
    _arguments = new std::string[_number_of_argument];

    int i = -1; // licznik
    size_t from, to; // od i do dla łuskania argumentów
    from = x;

    if(_number_of_argument != 0)
        data.push(e); // Zapamiętaj ostatni argument, oddzielonym ")"

    while(!data.empty()) // Jeżeli coś zapamiętaliśmy...
    {
        to = data.front(); // złap
        data.pop(); // zwal
        i++; // hopa
        _arguments[i] = command.substr(from, to-from); // mamy go!

        from = to+1; // i tak dalej
    }


}

std::string Command::Name()
{
    return _name;
}

std::string Command::Get(unsigned int arg)
{
    return _arguments[arg];
}

unsigned int Command::NumbersOfArgument()
{
    return _number_of_argument;
}

bool Command::isOk()
{
    return _ok;
}
