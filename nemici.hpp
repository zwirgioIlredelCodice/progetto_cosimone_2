
#include "strutture.h"

using namespace std;


class Goblin  // nemico che corre e fa danno se addosso al protagonista
{
protected:
    int life;
    int damage;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int value;  // quanto guadagna il protagonista se uccide questo nemico

public:
    Goblin(int life, int damage, WINDOW * win, char simbol, int yLoc, int xLoc, int value);

    void mvup();

    void mvdown();

    void mvleft();

    void mvright();

    int getmv();

    void display();

    void decreaseLife(int damage);

    void disappear(); // quando viene ucciso

};

class Arciere
{
protected:
    int life;
    weapon bow;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int value;  // valore guadagnato se si uccide questo nemico

public:
    Arciere(int life, weapon ar, WINDOW * win, int yLoc, int xLox, char simbol, int value);

    void decreaseLife(int damage);

    //funzione per sparare

    void display();

    void disappear(); // qunado viene eliminato
};