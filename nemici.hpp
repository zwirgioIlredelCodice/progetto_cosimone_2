
#ifndef PROGETTO_COSIMONE_2_NEMICI_HPP
#define PROGETTO_COSIMONE_2_NEMICI_HPP

#include "strutture.h"
#include "player.hpp"

using namespace std;


class Goblin  // nemico che corre e fa danno se addosso al protagonista
{
protected:
    Protagonista *p;
    int life;
    int damage;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int value;  // quanto guadagna il protagonista se uccide questo nemico
    bool alive;

public:
    Goblin(int life, int damage, WINDOW * win, char simbol, int yLoc, int xLoc, int value, Protagonista *p);

    void mvup();

    void mvdown();

    void mvleft();

    void mvright();

    void getmv();

    void display();

    void decreaseLife(int damage);

    void disappear(); // quando viene ucciso

    // ritorna il carattere
    char retChar();

    int positionX();

    int positionY();

    /*
     * funzione per controllare se è stato hittato
     */
    void checkDamage();

};

class Arciere
{
protected:
    Protagonista *p;
    int life;
    weapon bow;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int value;  // valore guadagnato se si uccide questo nemico
    bool alive;

public:
    Arciere(int life, weapon ar, WINDOW * win, int yLoc, int xLox, char simbol, int value, Protagonista *p);

    void decreaseLife(int damage);

    /*
     * funzione che spara quando il nostro personaggio è nel tiro
     */
    void shoot();

    void display();

    void disappear(); // quando viene eliminato
};


#endif //PROGETTO_COSIMONE_2_NEMICI_HPP