
#include "strutture.h"

using namespace std;


class Goblin  // nemico che corre e fa danno se addosso al protagonista
{
protected:
    int salute;
    int danno;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int guadagno;  // quanto guadagna il protagonista se uccide questo nemico

public:
    Goblin(int salute, int danno, WINDOW * win, char simbol, int yLoc, int xLoc, int guadagno);

    void mvup();

    void mvdown();

    void mvleft();

    void mvright();

    int getmv();

    void display();

    void subisci_danno(int danno);

    void sparisci(); // quando viene ucciso

};

class Arciere
{
protected:
    int salute;
    arma arco;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol;
    int guadagno;

public:
    Arciere(int salute, arma ar, WINDOW * win, int yLoc, int xLox, char simbol, int guadagno);

    void subisci_danno(int danno);

    //funzione per sparare

    void display();

    void sparisci();
};