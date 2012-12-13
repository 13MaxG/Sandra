#ifndef SYSTEM_H
#define SYSTEM_H


/**
 * @brief Główna klasa animacji.
 *
 * Zawiera wszystkie inormacje dotyczące animacji, przelicza je, oraz renderuje.
 * Jest to szablon, z niego powinny dziedziczyć właściwe animacjie.
 */
class System
{


public:
    System();

    void Load();
    void Update();
    void Render();

};

#endif // SYSTEM_H
