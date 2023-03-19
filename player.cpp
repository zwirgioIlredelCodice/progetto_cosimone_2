//
// Created by marco on 19/03/2023.
//

#include "player.hpp"

Protagonista::Protagonista(int life, int currency, weapon weap[], int n, WINDOW * win, int yLoc, int xLoc, char simbol)
{
    this->weap_index = 0;
    this->life = life;
    this->currency = currency;
    if (n > N_ARMI)
        this->n_weap = N_ARMI;
    else
        this->n_weap = n;
    for (int i = 0; i < this->n_weap; i++)
    {
        this->weapons[i].name = weapons[i].name;
        this->weapons[i].damage = weapons[i].damage;
        this->weapons[i].scope = weapons[i].scope;
    }
    this->curwin = win;
    this->xLoc = xLoc;
    this->yLoc = yLoc;
    getmaxyx(curwin, this->yMax, this->xMax);
    this->simbol = simbol;
}

void Protagonista::decreaseLife(int damage)
{
    this->life -= damage;
}

void Protagonista::increaseLife(int life)
{
    this->life += life;
}

void Protagonista::increaseCurrency(int currency)
{
    this->currency += currency;
}

void Protagonista::decreaseCurrency(int currency)
{
    this->currency -= currency;
}

void Protagonista::newWeapon(weapon Weapon)
{
    if (this->n_weap < N_ARMI)
    {
        this->weapons[n_weap].name = Weapon.name;
        this->weapons[n_weap].damage = Weapon.damage;
        this->weapons[n_weap].scope = Weapon.scope;
    }
    this->n_weap++;
}

void Protagonista::resetConsumable()
{
    // i potenziamenti devono essere registrati in modo tale da poter eliminare i consumabili
    // ogni volta che si esce dalla partita
}

void Protagonista::mvup()
{
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Protagonista::mvdown()
{
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax-2)
        yLoc = yMax-2;
}

void Protagonista::mvleft()
{
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Protagonista::mvright()
{
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc++;
    if (xLoc > xMax-2)
        xLoc = xMax-2;
}

int Protagonista::getmv()
{
    int choice = wgetch(curwin);
    switch (choice)
    {
        case KEY_UP:
            mvup();
            break;
        case KEY_DOWN:
            mvdown();
            break;
        case KEY_LEFT:
            mvleft();
            break;
        case KEY_RIGHT:
            mvright();
            break;
        default:
            break;
    }
    return choice;
}


void Protagonista::display()
{
    mvwaddch(curwin, yLoc, xLoc, simbol);
}

void Protagonista::shoot()
{
    int choice = wgetch(curwin);
    if (choice == 'c')   // da controllare se funziona

        for(int i = 0; i < weapons[weap_index].scope && i+xLoc <xMax; i++)
        {
            mvwaddch(curwin, yLoc, xLoc+i, ' ');
            mvwaddch(curwin, yLoc, xLoc+i+1, '-');
        }
}

