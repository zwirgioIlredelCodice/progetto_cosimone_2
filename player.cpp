//
// Created by marco on 19/03/2023.
//


#include "player.hpp"

Protagonista::Protagonista(mapList *curMap, int y, int x, char c, int life, int currency, weapon A[], int n)
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
    this->listMap = curMap;
    xLoc = x;
    yLoc = y;
    getmaxyx(listMap->getMap().win, yMax, xMax);
    keypad(listMap->getMap().win, 1);
    character = c;
}

void Protagonista::mvup() {
    if (mvwinch(listMap->getMap().win, yLoc - 1, xLoc) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc--;
        if (yLoc < 1)
            yLoc = 1;
        display();
    }
}

void Protagonista::mvdown() {
    if (mvwinch(listMap->getMap().win, yLoc + 1, xLoc) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc++;
        if (yLoc > yMax - 2)
            yLoc = yMax - 2;
        display();
    }
}

void Protagonista::mvleft() {
    if (mvwinch(listMap->getMap().win, yLoc, xLoc - 1) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc--;
        if (xLoc < 1)
            xLoc = 1;
        display();
    }
}

void Protagonista::mvright() {
    if (mvwinch(listMap->getMap().win, yLoc, xLoc + 1) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc++;
        if (xLoc > xMax - 2)
            xLoc = xMax - 2;
        display();
    }
}

int Protagonista::getmv(){
    int choice = wgetch(listMap->getMap().win);
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
        case 's':
            shot();
            break;
        case 'c':
            changeWeapon();
            break;
        case -1:
            break;
        default:
            break;
    }
    display();
    return choice;
}



void Protagonista::display()
{
    mvwprintw(stdscr, 30, 60, "                 ");
    mvwprintw(stdscr, 32, 60, "                             ");
    mvwprintw(stdscr, 30, 60, "Life : %d", getLife());
    mvwprintw(stdscr, 32, 60, "Currency : %d", getCurrency());
    mvwaddch(listMap->getMap().win, yLoc, xLoc, character);
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

void Protagonista::shot()
{
    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope && i + locx < xMax - 2) // && mvwinch(curMap.win, locy, locx + i + 1) != 'g' && mvwinch(curMap.win, locy, locx + i) != 'g'
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc + i, ' ');

        if (mvwinch(listMap->getMap().win, locy, locx + i + 1) == 'g')
        {
            listMap->checkGoblin(locy, locx + i + 1, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy, locx + i + 1) == 'a')
        {
            listMap->checkArciere(locy, locx + i + 1, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        mvwaddch(listMap->getMap().win, yLoc, xLoc + i + 1, '-');
        usleep(20000);
        wrefresh(listMap->getMap().win);
        i++;

        /*
        for (int j = 0; j < listMap->getGobNumber(); ++j)
        {
            listMap
        }
         */

    }
    //usleep(20000);
    mvwaddch(listMap->getMap().win, locy, locx + i, ' ');
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

int Protagonista::positionX()
{
    return xLoc;
}

int Protagonista::positionY()
{
    return yLoc;
}

char Protagonista::retChar()
{
    return character;
}

int Protagonista::retCurrentDamage()
{
    return weapons[weap_index].damage;
}

int Protagonista::retCurrentScope()
{
    return weapons[weap_index].scope;
}

int Protagonista::getLife()
{
    return life;
}

int Protagonista::getCurrency()
{
    return currency;
}

Protagonista::Protagonista() {}

int Protagonista::getN_weap() {
    return n_weap;
}

int Protagonista::getWeap_index() {
    return weap_index;
}

weapon *Protagonista::getWeapons() {
    return weapons;
}