#include "nemici.hpp"

Goblin::Goblin(int life, int damage, WINDOW * win, char simbol, int yLoc, int xLoc, int value, Protagonista *p)
{
    this->p = p;
    this->life = life;
    this->damage = damage;
    this->win = win;
    this->simbol = simbol;
    this->yLoc = yLoc;
    this->xLoc = xLoc;
    this->value = value;
    getmaxyx(win, this->yMax, this->xMax);
    this->alive = true;
}


void Goblin::mvup()
{
    if (mvwinch(win, yLoc - 1, xLoc) != p->retChar() && mvwinch(win, yLoc - 1, xLoc) != '-')
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
    if (mvwinch(win, yLoc + 1, xLoc) != p->retChar() && mvwinch(win, yLoc + 1, xLoc) != '-')
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
    if (mvwinch(win, yLoc, xLoc - 1) != p->retChar() && mvwinch(win, yLoc, xLoc - 2) != '-')
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
    if(mvwinch(win, yLoc, xLoc + 1) != p->retChar() && mvwinch(win, yLoc, xLoc + 1) != '-')
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
    p->increaseCurrency(this->value);
}

int Goblin::positionY()
{
    return yLoc;
}

int Goblin::positionX()
{
    return xLoc;
}

void Goblin::checkDamage()
{
    if (p->positionY() == yLoc && p->positionX() < xLoc && p->positionX() + p->retCurrentScope() >= xLoc)
    {
        decreaseLife(p->retCurrentDamage());
    }
}


//-----------------------------------------

Arciere::Arciere(int life, weapon ar, WINDOW *win, int yLoc, int xLox, char simbol, int value, Protagonista *p)
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
            shoot();
        }
        mvwaddch(win, yLoc, xLoc, this->simbol);
    }
}

void Arciere::disappear()
{
    this->simbol == ' ';
    Arciere::display();
    alive = false;
    p->increaseCurrency(value);
}

void Arciere::shoot()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && locx - i > 2) // && mvwinch(curwin, locy, locx + i + 1) != 'g' && mvwinch(curwin, locy, locx + i) != 'g'{
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 8000 == 0)
        {
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