#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>

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