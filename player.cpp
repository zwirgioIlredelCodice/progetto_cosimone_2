//
// Created by marco on 19/03/2023.
//


#include "player.hpp"

Protagonista::Protagonista(mapList* curMap, int y, int x, char c, int life, int currency, int baseDamage, int baseRange,
                           int armor, int salesPercent, int coinPercent, int difficulty , weapon A[], int n)
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

    this->baseDamage = baseDamage;
    this->baseRange = baseRange;
    this->armor = armor;
    this->salesPercent = salesPercent;
    this->coinPercent = coinPercent;
    this->difficulty = difficulty;
}

void Protagonista::mvup() {
    if (mvwinch(listMap->getMap().win, yLoc - 1, xLoc) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc--;
        display();
    }
    else if (mvwinch(listMap->getMap().win, yLoc - 1, xLoc) == '$')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc--;
        display();
        increaseCurrency(3); // valore monete raccolte
    }
    else if (mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == '.')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc--;
        display();
        increaseLife(3); //valore vita raccolta
    }
    else if (mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == '<' || mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == '>')
    {
        mvdown();
        display();
        decreaseLife(2);
    }
    else if (this->currency >= 2 && (mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == 'W' ||
             mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == 'A' ||
             mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == 'T' ||
             mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == 'E' ||
             mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == 'R' ||
             mvwinch (listMap->getMap().win, yLoc - 1, xLoc) == '~'))
    {
        mvwaddch (listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc--;
        display();
        decreaseCurrency(2);
    }
}


void Protagonista::mvdown() {
    if (mvwinch(listMap->getMap().win, yLoc + 1, xLoc) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc++;
        display();
    }
    else if (mvwinch(listMap->getMap().win, yLoc + 1, xLoc) == '$')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc++;
        display();
        increaseCurrency(3); // valore monete raccolte
    }
    else if (mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == '.')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc++;
        display();
        increaseLife(3); //valore vita raccolta
    }
    else if (mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == '<' || mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == '>')
    {
        mvup();
        display();
        decreaseLife(2);
    }
    else if (this->currency >= 2 && (mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == 'W' ||
             mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == 'A' ||
             mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == 'T' ||
             mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == 'E' ||
             mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == 'R' ||
             mvwinch (listMap->getMap().win, yLoc + 1, xLoc) == '~'))
    {
        mvwaddch (listMap->getMap().win, yLoc, xLoc, ' ');
        yLoc++;
        display();
        decreaseCurrency(2);
    }
}

void Protagonista::mvleft() {
    if (mvwinch(listMap->getMap().win, yLoc, xLoc - 1) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc--;
        display();
    }
    else if (mvwinch(listMap->getMap().win, yLoc, xLoc - 1) == '$')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc--;
        display();
        increaseCurrency(3); // valore monete raccolte
    }
    else if (mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == '.')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc--;
        display();
        increaseLife(3); //valore vita raccolta
    }
    else if (mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == '>')
    {
        mvright();
        display();
        decreaseLife(2);
    }
    else if (this->currency >= 2 && (mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == 'W' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == 'A' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == 'T' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == 'E' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == 'R' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc - 1) == '~'))
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc--;
        display();
        decreaseCurrency(2);
    }
}

void Protagonista::mvright() {
    if (mvwinch(listMap->getMap().win, yLoc, xLoc + 1) == ' ')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc++;
        display();
    }
    else if (mvwinch(listMap->getMap().win, yLoc, xLoc + 1) == '$')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc++;
        display();
        increaseCurrency(3); // valore monete raccolte
    }
    else if (mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == '.')
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc++;
        display();
        increaseLife(3); //valore vita raccolta
    }
    else if (mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == '<')
    {
        mvleft();
        display();
        decreaseLife(2);
    }
    else if (this->currency >= 2 && (mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == 'W' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == 'A' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == 'T' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == 'E' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == 'R' ||
             mvwinch (listMap->getMap().win, yLoc, xLoc + 1) == '~'))
    {
        mvwaddch(listMap->getMap().win, yLoc, xLoc, ' ');
        xLoc++;
        display();
        decreaseCurrency(2);
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
        case 'd':
            shotRight();
            break;
        case 'a':
            shotLeft();
            break;
        case 's':
            shotDown();
            break;
        case 'c':
            changeWeapon();
            break;
        case 'w':
            shotUp();
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
    mvwprintw(stdscr, MAP_YMAX, 0, "Difficulty : %d", getDifficulty());
    mvwprintw(stdscr, MAP_YMAX + 1, 10, "Life : %d     ", getLife());
    mvwprintw(stdscr, MAP_YMAX + 2, 10, "Currency : %d     ", getCurrency());
    mvwprintw(stdscr, MAP_YMAX + 3, 10, "Weapon : %s, damage: %d, range: %d      ", weapons[weap_index].name.c_str(), weapons[weap_index].damage, weapons[weap_index].scope);
    mvwprintw(stdscr, MAP_YMAX + 4, 10, "Map #%d   ", listMap->getIndex());
    mvwprintw(stdscr, MAP_YMAX + 5, 10, "CONTROLS: movement: arrow keys, shoot: WASD, change weapon: C, menu: M");
    mvwprintw(stdscr, MAP_YMAX + 6, 10, "Guide: go near '[' ']' char to switch rooms");
    mvwprintw(stdscr, MAP_YMAX + 10, 2, "'.' adds life, '<>' damages you");
    mvwprintw(stdscr, MAP_YMAX + 11, 2, "'$' adds money, 'WATER' makes you lose money");
    mvwprintw(stdscr, MAP_YMAX + 12, 2,"'a', 's', 'g' are enemies");
    mvwaddch(listMap->getMap().win, yLoc, xLoc, character);
}

void Protagonista::decreaseLife(int damage)
{
    this->life -= (damage - armor);
}

void Protagonista::increaseLife(int life)
{
    this->life += life;
}

void Protagonista::increaseCurrency(int currency)
{
    this->currency += (currency * coinPercent) / 100;
}

void Protagonista::decreaseCurrency(int currency)
{
    this->currency -= (currency - (currency % 100) * salesPercent);
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

void Protagonista::shotRight()
{
    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope  && (mvwinch(listMap->getMap().win, locy, i + locx) == ' ' || mvwinch(listMap->getMap().win, locy, i + locx ) == '-') || mvwinch(listMap->getMap().win, locy, i + locx ) == 'a' || mvwinch(listMap->getMap().win, locy, i + locx ) == 'g' || mvwinch(listMap->getMap().win, locy, i + locx ) == 's') // && mvwinch(curMap.win, locy, locx + i + 1) != 'g' && mvwinch(curMap.win, locy, locx + i) != 'g'
    {
        if (i > 1)
        {
            mvwaddch(listMap->getMap().win, yLoc, xLoc + i - 1, ' ');
        }

        if (mvwinch(listMap->getMap().win, locy, locx + i) == 'g')
        {
            listMap->checkGoblin(locx + i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy, locx + i) == 'a')
        {
            listMap->checkArciere(locx + i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy, locx + i) == 's')
        {
            listMap->checkSicario(locx + i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }


        mvwaddch(listMap->getMap().win, yLoc, xLoc + i, '-');
        usleep(20000);
        wrefresh(listMap->getMap().win);
        i++;

    }
    mvwaddch(listMap->getMap().win, locy, locx + i - 1, ' ');
    wrefresh(listMap->getMap().win);
}

void Protagonista::shotLeft()
{
    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope  && (mvwinch(listMap->getMap().win, locy, locx - i) == ' ' || mvwinch(listMap->getMap().win, locy, locx - i) == '-') || mvwinch(listMap->getMap().win, locy, locx - i) == 'a' || mvwinch(listMap->getMap().win, locy, -i + locx ) == 'g' || mvwinch(listMap->getMap().win, locy, -i + locx ) == 's') // && mvwinch(curMap.win, locy, locx + i + 1) != 'g' && mvwinch(curMap.win, locy, locx + i) != 'g'
    {
        if (i > 1)
        {
            mvwaddch(listMap->getMap().win, yLoc, xLoc - i + 1, ' ');
        }

        if (mvwinch(listMap->getMap().win, locy, locx - i ) == 'g')
        {
            listMap->checkGoblin(locx - i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy, locx - i ) == 'a')
        {
            listMap->checkArciere(locx - i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy, locx - i ) == 's')
        {
            listMap->checkSicario(locx - i , locy, Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        mvwaddch(listMap->getMap().win, yLoc, xLoc - i, '-');
        usleep(20000);
        wrefresh(listMap->getMap().win);
        i++;

    }
    mvwaddch(listMap->getMap().win, locy, locx - i + 1, ' ');
}

void Protagonista::shotDown()
{
    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope  && (mvwinch(listMap->getMap().win, locy + i , locx) == ' ' || mvwinch(listMap->getMap().win, locy + i, locx) == '-') || mvwinch(listMap->getMap().win, locy + i,  locx ) == 'a' || mvwinch(listMap->getMap().win, locy + i, locx ) == 'g' || mvwinch(listMap->getMap().win, locy + i, locx ) == 's') // && mvwinch(curMap.win, locy, locx + i + 1) != 'g' && mvwinch(curMap.win, locy, locx + i) != 'g'
    {
        if (i > 1)
        {
            mvwaddch(listMap->getMap().win, yLoc + i - 1, xLoc , ' ');
        }

        if (mvwinch(listMap->getMap().win, locy + i , locx) == 'g')
        {
            listMap->checkGoblin(locx, locy + i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy + i , locx) == 'a')
        {
            listMap->checkArciere(locx, locy + i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy + i , locx) == 's')
        {
            listMap->checkSicario(locx, locy + i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        mvwaddch(listMap->getMap().win, yLoc + i, xLoc, '|');
        usleep(20000);
        wrefresh(listMap->getMap().win);
        i++;

    }
    mvwaddch(listMap->getMap().win, locy + i - 1, locx, ' ');
}

void Protagonista::shotUp()
{
    int i = 1;
    int locy = yLoc;
    int locx = xLoc;
    while( i < weapons[weap_index].scope  && (mvwinch(listMap->getMap().win, locy - i , locx) == ' ' || mvwinch(listMap->getMap().win, locy - i, locx) == '-') || mvwinch(listMap->getMap().win, locy - i,  locx ) == 'a' || mvwinch(listMap->getMap().win, locy - i, locx ) == 'g' || mvwinch(listMap->getMap().win, locy - i, locx ) == 's')
    {
        if (i > 1)
        {
            mvwaddch(listMap->getMap().win, yLoc - i + 1, xLoc , ' ');
        }

        if (mvwinch(listMap->getMap().win, locy - i , locx) == 'g')
        {
            listMap->checkGoblin(locx, locy - i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy - i , locx) == 'a')
        {
            listMap->checkArciere(locx, locy - i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        if (mvwinch(listMap->getMap().win, locy - i , locx) == 's')
        {
            listMap->checkSicario(locx, locy - i , Protagonista::retCurrentDamage());
            break;
            // segnale che vada a controllare e effettuare danno al nemico della mappa
        }

        mvwaddch(listMap->getMap().win, yLoc - i, xLoc, '|');
        usleep(20000);
        wrefresh(listMap->getMap().win);
        i++;

    }
    mvwaddch(listMap->getMap().win, locy - i + 1, locx, ' ');
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
    return weapons[weap_index].damage + baseDamage;
}

int Protagonista::retCurrentScope()
{
    return weapons[weap_index].scope + baseRange;
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

mapList *Protagonista::getMapList() {
    return listMap;
}

void Protagonista::setMapList(mapList* ml) {
    this->listMap = ml;
}

int Protagonista::getDifficulty() {
    return difficulty;
}

void Protagonista::changeDifficulty(int value) {
    if (difficulty + value >= 0) difficulty += value;
}

void Protagonista::increaseBaseDamage(int value) {
    baseDamage += value;
}

void Protagonista::increaseBaseRange(int value) {
    baseRange += value;
}

void Protagonista::increaseArmor(int value) {
    armor += value;
}

void Protagonista::increaseSalesPercent(int value) {
    if (salesPercent + value < 100) {
        salesPercent += value;
    }
}

void Protagonista::increaseCoinPercent(int value) {
    coinPercent += value;
}

int Protagonista::getBaseDamage() {
    return baseDamage;
}

int Protagonista::getBaseRange() {
    return baseRange;
}

int Protagonista::getArmor() {
    return armor;
}

int Protagonista::getCoinPercent() {
    return coinPercent;
}

int Protagonista::getSalesPercent() {
    return salesPercent;
}

void Protagonista::goToStartPosition()
{
    mvwaddch(listMap->getWin(), yLoc, xLoc, ' ');
    xLoc = 1;
    yLoc = 1;
    display();
}

bool Protagonista::isDead() {
    if (life > 0) {
        return false;
    }
    else {
        return true;
    }
}

