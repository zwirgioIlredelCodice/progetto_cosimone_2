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
    else mvleft();
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
    else mvright();
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
    else
        mvdown();
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
    else
        mvup();
}

void Goblin::getmv()
{
    if (alive)
    {
        bool choice;
        if (yLoc > p->positionY() && xLoc > p->positionX())
            (choice ? mvup() : mvleft());
        else if (yLoc > p->positionY() && xLoc < p->positionX())
            (choice ? mvup() : mvright());
        else if (yLoc < p->positionY() && xLoc > p->positionX())
            (choice ? mvdown() : mvleft());
        else if (yLoc < p->positionY() && xLoc < p->positionX())
            (choice ? mvdown() : mvright());
        else if (xLoc == p->positionX())
            (yLoc > p->positionY() ? mvup() : mvdown());
        else if (yLoc == p->positionY())
            (xLoc > p->positionX() ? mvleft() : mvright());
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
    this->simbol = ' ';
    p->increaseCurrency(value);
    Goblin::display();
    alive = false;
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

char Goblin::retChar() {
    return this->simbol;
}

int Goblin::retDamage() {
    return this->damage;
}

bool Goblin::retAlive() {
    return this->alive;
}

//-----------------------------------------

Arciere::Arciere(int life, int damage, WINDOW *win, int yLoc, int xLox, int value, Protagonista *p)
{
    this->life = life;
    this->bow.scope = 100;
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
        mvwaddch(win, yLoc, xLoc, this->simbol);
        if (yLoc == p->positionY())
        {
            if (xLoc > p->positionX() && xLoc - bow.scope <= p->positionX())
            {
                shotLeft();
            }
            else if (xLoc < p->positionX() && xLoc + bow.scope >= p->positionX())
            {
                shotRight();
            }
        }
    }
}

void Arciere::disappear()
{
    this->simbol = ' ';
    mvwaddch(win, yLoc, xLoc, ' ');
    alive = false;
    p->increaseCurrency(value);
}

void Arciere::shotLeft()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && (mvwinch(win, locy, locx - i) == ' ' || mvwinch(win, locy, locx - i) == '-' || mvwinch(win, locy, locx - i) == p->retChar()))
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 5000 == 0)
        {
            if (i > 1)
            {
                mvwaddch(win, yLoc, xLoc - i + 1, ' ');
            }

            if (mvwinch(win, locy, locx - i ) == p->retChar())
            {
                p->decreaseLife(retCurrentDamage());
                break;
            }
            mvwaddch(win, locy, locx - i , '-');
            wrefresh(win);
            i++;
        }

        p->getmv();
        p->display();

    }
        mvwaddch(win, locy, locx - i + 1, ' ');
}

void Arciere::shotRight()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && (mvwinch(win, locy, locx + i) == ' ' || mvwinch(win, locy, locx + i) == '-' || mvwinch(win, locy, locx + i) == p->retChar()))
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 5000 == 0)
        {
            if (i > 1)
            {
                mvwaddch(win, yLoc, xLoc + i - 1, ' ');
            }

            if (mvwinch(win, locy, locx + i ) == p->retChar())
            {
                p->decreaseLife(retCurrentDamage());
                break;
            }
            mvwaddch(win, locy, locx + i , '-');
            wrefresh(win);
            i++;
        }
        p->getmv();
        p->display();

    }
    mvwaddch(win, locy, locx + i - 1, ' ');
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

bool Arciere::retAlive() {
    return this->alive;
}


//--------------------------------------------------------------------------

Sicario::Sicario(int life, int damage, WINDOW *win, int yLoc, int xLox, int value, Protagonista *p)
{
    this->life = life;
    this->bow.scope = 25;
    this->bow.name = "Gun";
    this->bow.damage = damage;
    this->win = win;
    this->simbol = 's';
    this->value = value;
    this->yLoc = yLoc;
    this->xLoc = xLox;
    getmaxyx(win, this->yMax, this->xMax);
    this->p = p;
    this->alive = true;
}

void Sicario::decreaseLife(int damage)
{
    this->life -= damage;
    display();
    if (this->life <= 0)
        disappear();
}

void Sicario::display()
{
    if (alive)
    {
        mvwaddch(win, yLoc, xLoc, this->simbol);
    }
}

void Sicario::disappear()
{
    this->simbol = ' ';
    mvwaddch(win, yLoc, xLoc, ' ');
    alive = false;
    p->increaseCurrency(value);
}

void Sicario::shotLeft()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && (mvwinch(win, locy, locx - i) == ' ' || mvwinch(win, locy, locx - i) == '-' || mvwinch(win, locy, locx - i) == p->retChar()))
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 9000 == 0)
        {
            if (i > 1)
            {
                mvwaddch(win, yLoc, xLoc - i + 1, ' ');
            }

            if (mvwinch(win, locy, locx - i ) == p->retChar())
            {
                p->decreaseLife(retCurrentDamage());
                break;
            }
            mvwaddch(win, locy, locx - i , '-');
            wrefresh(win);
            i++;
        }
        p->getmv();
        p->display();

    }
    mvwaddch(win, locy, locx - i + 1, ' ');
}

void Sicario::shotRight()
{

    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    auto startTime = chrono::steady_clock::now();
    while (i < bow.scope && (mvwinch(win, locy, locx + i) == ' ' || mvwinch(win, locy, locx + i) == '-' || mvwinch(win, locy, locx + i) == p->retChar()))
    {
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 9000 == 0)
        {
            if (i > 1)
            {
                mvwaddch(win, yLoc, xLoc + i - 1, ' ');
            }

            if (mvwinch(win, locy, locx + i ) == p->retChar())
            {
                p->decreaseLife(retCurrentDamage());
                break;
            }
            mvwaddch(win, locy, locx + i , '-');
            wrefresh(win);
            i++;
        }
        p->getmv();
        p->display();

    }
    mvwaddch(win, locy, locx + i - 1, ' ');
}

int Sicario::retLife()
{
    return this->life;
}

int Sicario::retValue()
{
    return this->value;
}

int Sicario::positionX()
{
    return this->xLoc;
}

int Sicario::positionY()
{
    return this->yLoc;
}

int Sicario::retCurrentDamage()
{
    return bow.damage;
}

bool Sicario::retAlive() {
    return this->alive;
}

void Sicario::mvup()
{
    if (mvwinch(win, yLoc - 1, xLoc) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        yLoc--;
        if (yLoc < 1)
            yLoc = 1;
    }
}

void Sicario::mvdown()
{
    if (mvwinch(win, yLoc + 1, xLoc) == ' ')
    {
        mvwaddch(win, yLoc, xLoc, ' ');
        yLoc++;
        if (yLoc > yMax - 2)
            yLoc = yMax - 2;
    }
}

void Sicario::getmv()
{
    if (alive)
    {
        if (yLoc == p->positionY())
        {
            if (xLoc > p->positionX() && xLoc - bow.scope <= p->positionX())
            {
                shotLeft();
            }
            else if (xLoc < p->positionX() && xLoc + bow.scope >= p->positionX())
            {
                shotRight();
            }
        }
    }
}

void Sicario::move()
{
    if (alive)
    {
        if (yLoc != p->positionY()) {
            (yLoc > p->positionY() ? mvup() : mvdown());
        }
    }
}