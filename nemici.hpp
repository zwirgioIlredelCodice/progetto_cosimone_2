
#ifndef PROGETTO_COSIMONE_2_NEMICI_HPP
#define PROGETTO_COSIMONE_2_NEMICI_HPP

#include "strutture.h"
#include "player.hpp"

using namespace std;

class Protagonista;

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
    Goblin(int life, int damage, WINDOW * win, int yLoc, int xLoc, int value, Protagonista *p);

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

    /*
     * ritorna la vita attuale del goblin
     */
    int retLife();

    int retDamage();

    int positionX();

    int positionY();

    /*
     * ritorna il valore che si ottiene uccidendo il goblin
     */
    int retValue();
    bool retAlive();
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
    Arciere(int life, int damage, WINDOW * win, int yLoc, int xLox, int value, Protagonista *p);

    void decreaseLife(int damage);

    /*
     * funzione che spara quando il nostro personaggio è nel tiro
     */
    void shotLeft();

    void shotRight();

    void display();

    void disappear(); // quando viene eliminato

    /*
     * ritorna la vita attuale dell' arciere
     */
    int retLife();

    /*
     * ritorna il valore che si ottiene uccidendo l'arciere
     */
    int retValue();

    int positionX();

    int positionY();

    int retCurrentDamage();

    bool retAlive();
};

class Sicario
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
    Sicario(int life, int damage, WINDOW * win, int yLoc, int xLox, int value, Protagonista *p);

    void decreaseLife(int damage);

    /*
     * funzione che spara quando il nostro personaggio è nel tiro
     */
    void shotRight();

    void shotLeft();

    void display();

    void disappear(); // quando viene eliminato

    /*
     * ritorna la vita attuale dell' arciere
     */
    int retLife();

    /*
     * ritorna il valore che si ottiene uccidendo l'arciere
     */
    int retValue();

    int positionX();

    int positionY();

    int retCurrentDamage();

    bool retAlive();

    void mvup();

    void mvdown();

    void getmv();

    void move();
};


#endif //PROGETTO_COSIMONE_2_NEMICI_HPP