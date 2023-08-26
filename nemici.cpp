#include "nemici.hpp"

Goblin::Goblin(int life, int damage, WINDOW * win, int yLoc, int xLoc, int value, Protagonista *p)
{
    this->p = p;
    this->life = life;
    this->damage = damage;
    this->win = win;
    this->simbol = 'g';
    this->yLoc = yLoc;
    this->xLoc = xLoc;
    this->value = value;
    getmaxyx(win, this->yMax, this->xMax);
    this->alive = true;
}


void Goblin::mvup()
{
    if (mvwinch(win, yLoc - 1, xLoc) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        yLoc--;
        if (yLoc < 1)
            yLoc = 1;
    }
    else if (mvwinch(win, yLoc - 1, xLoc) == p->retChar())
    {
        p->decreaseLife(this->damage);
    }
}

void Goblin::mvdown()
{
    if (mvwinch(win, yLoc + 1, xLoc) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        yLoc++;
        if (yLoc > yMax - 2)
            yLoc = yMax - 2;
    }
    else if (mvwinch(win, yLoc + 1, xLoc) == p->retChar())
    {
        p->decreaseLife(this->damage);
    }
}

void Goblin::mvleft()
{
    if (mvwinch(win, yLoc, xLoc - 1) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        xLoc--;
        if (xLoc < 1)
            xLoc = 1;
    }
    else if(mvwinch(win, yLoc, xLoc - 1) == p->retChar())
    {
        p->decreaseLife(this->damage);
    }
}

void Goblin::mvright()
{
    if(mvwinch(win, yLoc, xLoc + 1) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        xLoc++;
        if (xLoc > xMax - 2)
            xLoc = xMax - 2;
    }
    else if (mvwinch(win, yLoc, xLoc + 1) == p->retChar())
    {
        p->decreaseLife(this->damage);
    }
}

void Goblin::getmv()
{
    if (alive)
    {
        if (yLoc > p->positionY())
            mvup();
        else if (yLoc < p->positionY())
            mvdown();
        else if (xLoc > p->positionX())
            mvleft();
        else if (xLoc < p->positionX())
            mvright();
    }
}

void Goblin::display()
{
    if(alive)
    {
        mvwaddch(win, yLoc, xLoc, simbol);
    }
}

void Goblin::decreaseLife(int damage)
{
    this->life -= damage;
    if (this->life <= 0)
        Goblin::disappear();
}

/*
 * funzione che fa "scomparire" l'oggetto
 */

void Goblin::disappear()
{
    alive = false;
    this->simbol = ' ';
    Goblin::display();
}

int Goblin::positionY()
{
    return yLoc;
}

int Goblin::positionX()
{
    return xLoc;
}

int Goblin::retLife()
{
    return this->life;
}

int Goblin::retValue()
{
    return this->value;
}


//-----------------------------------------

Arciere::Arciere(int life, int damage, WINDOW *win, int yLoc, int xLox, int value, Protagonista *p)
{
    this->life = life;
    this->bow.scope = 10;
    this->bow.name = "Bow";
    this->bow.damage = damage;
    this->win = win;
    this->simbol = 'a';
    this->value = value;
    this->yLoc = yLoc;
    this->xLoc = xLox;
    getmaxyx(win, this->yMax, this->xMax);
    this->p = p;
    this->alive = true;
}

void Arciere::decreaseLife(int damage)
{
    this->life -= damage;
    if (this->life <= 0)
        Arciere::disappear();
}

void Arciere::display()
{
    if (alive)
    {
        if (yLoc == p->positionY()) {
            shot();
        }
        mvwaddch(win, yLoc, xLoc, this->simbol);
    }
}

void Arciere::disappear()
{
    this->simbol = ' ';
    Arciere::display();
    alive = false;
    p->increaseCurrency(value);
}

void Arciere::shot()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && locx - i > 2)
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 8000 == 0)
        {
            if (mvwinch(win, locy, locx - i- 1) == p->retChar())
            {
                p->decreaseLife(retCurrentDamage());
            }
            mvwaddch(win, locy, locx - i, ' ');
            mvwaddch(win, locy, locx - i - 1, '-');
            wrefresh(win);
            i++;
        }
        p->getmv();
        p->display();

    }
   // if (mvwinch(win, locy, locx - i) != p->retChar())
        mvwaddch(win, locy, locx - i, ' ');
}

int Arciere::retLife()
{
    return this->life;
}

int Arciere::retValue()
{
    return this->value;
}

int Arciere::positionX()
{
    return this->xLoc;
}

int Arciere::positionY()
{
    return this->yLoc;
}

int Arciere::retCurrentDamage()
{
    return bow.damage;
}