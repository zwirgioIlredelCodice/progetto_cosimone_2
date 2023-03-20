//
// Created by marco on 19/03/2023.
//


#include "player.hpp"

Protagonista::Protagonista(WINDOW *win, int y, int x, char c, int life, int currency, weapon A[], int n)
{
    if (n > N_ARMI)
        this->n_weap = N_ARMI;
    else
        this->n_weap = n;
    for (int i = 0; i < n_weap; i++)
    {
        this->weapons[i].name = A[i].name;
        this->weapons[i].damage = A[i].damage;
        this->weapons[i].scope = A[i].scope;
    }
    this->weap_index = 0;
    this->life = life;
    this->currency = currency;
    curwin = win;
    xLoc = x;
    yLoc = y;
    getmaxyx(curwin, yMax, xMax);
    keypad(curwin, 1);
    character = c;
}

void Protagonista::mvup() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Protagonista::mvdown() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax-2)
        yLoc = yMax-2;
}

void Protagonista::mvleft() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Protagonista::mvright() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc++;
    if (xLoc > xMax-2)
        xLoc = xMax-2;
}

int Protagonista::getmv(){
    int choice = wgetch(curwin);
    switch (choice) {
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
        case 'c':
            shoot();
            break;
        case 's':
            changeWeapon();
            break;
        default:
            break;
    }
    return choice;
}


void Protagonista::display() {
    mvwaddch(curwin, yLoc, xLoc, character);
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

void Protagonista::shoot()
{
    int i = 0;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope && i+xLoc < xMax - 3)
    {
        mvwaddch(curwin, yLoc, xLoc + i + 1, ' ');
        mvwaddch(curwin, yLoc, xLoc + i + 2, '-');
        usleep(1000);
        wrefresh(curwin);
        i++;
    }
    mvwaddch(curwin, locy, locx + i + 1, ' ');


}

void Protagonista::changeWeapon()
{
    if (weap_index + 1 >= n_weap)
    {
        weap_index = 0;
    }
    else
    {
        weap_index ++;
    }
}