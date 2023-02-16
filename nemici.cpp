#include "nemici.hpp"

Goblin::Goblin(int salute, int danno, WINDOW * win, char simbol, int yLoc, int xLoc, int guadagno)
{
    this->salute = salute;
    this->danno = danno;
    this->win = win;
    this->simbol = simbol;
    this->yLoc = yLoc;
    this->xLoc = xLoc;
    this->guadagno = guadagno;
    getmaxyx(win, this->yMax, this->xMax);
}


void Goblin::mvup()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Goblin::mvdown()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax-2)
        yLoc = yMax-2;
}

void Goblin::mvleft()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Goblin::mvright()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    xLoc++;
    if (xLoc > xMax-2)
        xLoc = xMax-2;
}

int Goblin::getmv()
{
    srand(time(NULL));
    int choice = rand() % 4;
    switch (choice) {
        case 0:
            mvup();
            break;
        case 1:
            mvdown();
            break;
        case 2:
            mvleft();
            break;
        case 3:
            mvright();
            break;
        default:
            break;
    }
    return choice;
}


void Goblin::display()
{
    mvwaddch(win, yLoc, xLoc, simbol);
}

void Goblin::subisci_danno(int danno)
{
    this->salute -= danno;
}

void Goblin::sparisci()
{
    this->simbol = ' ';   //mette il simbolo a spazio così non viene visto
    Goblin::display();
}


//-----------------------------------------

Arciere::Arciere(int salute, arma ar, WINDOW *win, int yLoc, int xLox, char simbol, int guadagno)
{
    this->salute = salute;
    this->arco.portata = ar.portata;
    this->arco.nome = "Arco";
    this->arco.danno = ar.danno;
    this->win = win;
    this->simbol = simbol;
    this->guadagno = guadagno;
    this->yLoc = yLoc;
    this->xLoc = xLox;
    getmaxyx(win, this->yMax, this->xMax);
}

void Arciere::subisci_danno(int danno)
{
    this->salute -= danno;
}

void Arciere::display()
{
    mvwaddch(win, yLoc, xLoc, this->simbol);
}

void Arciere::sparisci()
{
    this->simbol == ' ';
    Arciere::display();
}