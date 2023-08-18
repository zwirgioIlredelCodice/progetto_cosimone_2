//
// Created by marco on 19/03/2023.
//


#include "player.hpp"

Protagonista::Protagonista(map curMap, int y, int x, char c, int life, int currency, weapon A[], int n)
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
    this->curMap = curMap;
    xLoc = x;
    yLoc = y;
    getmaxyx(curMap.win, yMax, xMax);
    keypad(curMap.win, 1);
    character = c;
}

void Protagonista::mvup() {
    if (mvwinch(curMap.win, yLoc - 1, xLoc) != 'g')
    {
        mvwaddch(curMap.win, yLoc, xLoc, ' ');
        yLoc--;
        if (yLoc < 1)
            yLoc = 1;
    }
}

void Protagonista::mvdown() {
    if (mvwinch(curMap.win, yLoc + 1, xLoc) != 'g')
    {
        mvwaddch(curMap.win, yLoc, xLoc, ' ');
        yLoc++;
        if (yLoc > yMax - 2)
            yLoc = yMax - 2;
    }
}

void Protagonista::mvleft() {
    if (mvwinch(curMap.win, yLoc, xLoc - 1) != 'g')
    {
        mvwaddch(curMap.win, yLoc, xLoc, ' ');
        xLoc--;
        if (xLoc < 1)
            xLoc = 1;
    }
}

void Protagonista::mvright() {
    if (mvwinch(curMap.win, yLoc, xLoc + 1) != 'g')
    {
        mvwaddch(curMap.win, yLoc, xLoc, ' ');
        xLoc++;
        if (xLoc > xMax - 2)
            xLoc = xMax - 2;
    }
}

int Protagonista::getmv(){
    int choice = wgetch(curMap.win);
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
    return choice;
}


void Protagonista::display()
{
    mvwprintw(stdscr, 30, 60, "                 ");
    mvwprintw(stdscr, 32, 60, "                             ");
    mvwaddch(curMap.win, yLoc, xLoc, character);
    mvwprintw(stdscr, 30, 60, "Life : %d", getLife());
    mvwprintw(stdscr, 32, 60, "Currency : %d", getCurrency());
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
        mvwaddch(curMap.win, yLoc, xLoc + i, ' ');
        mvwaddch(curMap.win, yLoc, xLoc + i + 1, '-');
        usleep(20000);
        wrefresh(curMap.win);
        i++;
    }
    usleep(20000);
//    if (mvwinch(curMap.win, locy, locx + i) != 'g')
    mvwaddch(curMap.win, locy, locx + i, ' ');
//    else
//        return make_pair(locy, locx + i);
    // altrimenti ho hittato un nemico
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

void Protagonista::changeMap(map nMap)
{
    curMap = nMap;
}