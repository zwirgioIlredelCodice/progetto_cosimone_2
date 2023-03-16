#include "nemici.hpp"

Goblin::Goblin(int life, int damage, WINDOW * win, char simbol, int yLoc, int xLoc, int value)
{
    this->life = life;
    this->damage = damage;
    this->win = win;
    this->simbol = simbol;
    this->yLoc = yLoc;
    this->xLoc = xLoc;
    this->value = value;
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

void Goblin::decreaseLife(int damage)
{
    this->life -= damage;
    if (this->life <= 0)
        Goblin::disappear();
}

void Goblin::disappear()
{
    this->simbol = ' ';   //mette il simbolo a spazio così non viene visto
    Goblin::display();
}


//-----------------------------------------

Arciere::Arciere(int life, weapon ar, WINDOW *win, int yLoc, int xLox, char simbol, int value)
{
    this->life = life;
    this->bow.scope = ar.scope;
    this->bow.name = "Bow";
    this->bow.damage = ar.damage;
    this->win = win;
    this->simbol = simbol;
    this->value = value;
    this->yLoc = yLoc;
    this->xLoc = xLox;
    getmaxyx(win, this->yMax, this->xMax);
}

void Arciere::decreaseLife(int damage)
{
    this->life -= damage;
    if (this->life <= 0)
        Arciere::disappear();
}

void Arciere::display()
{
    mvwaddch(win, yLoc, xLoc, this->simbol);
}

void Arciere::disappear()
{
    this->simbol == ' ';
    Arciere::display();
}