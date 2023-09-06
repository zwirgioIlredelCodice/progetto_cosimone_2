//
// Created by alice on 08/08/23.
//

#include "mapList.hpp"


void mapList::add(map m) {
    if (n >= max_n) { // allungare l'array del doppio
        max_n *= 2;
        map* tmp = new map[max_n];
        // copio le mappe dell'array
        for (int i = 0; i < n; i++) {
            tmp[i] = maps[i];
        }
        // libero la memoria del vecchio array
        delete maps;
        // sostituisco l'array
        maps = tmp;
    }
    maps[n] = m;
    n++;
}

void mapList::clear() {
    n = 0;
    index = 0;
}

void mapList::next(){
    if (index < n-1)
        index++;

};

void mapList::prev() {
    if (index > 0)
        index--;

}


void mapList::checkGoblin(int x, int y, int damage){
    bool flag = false;
    int i=0;
    while (!flag && i < maps[index].gobIndex){
        if (maps[index].gob[i]->positionX() == x && maps[index].gob[i]->positionY() == y) {
            maps[index].gob[i]->decreaseLife(damage);
            flag=true;
        }
        i++;
    }
}

void mapList::checkArciere(int x, int y, int damage) {
    bool flag = false;
    int i=0;
    while (!flag && i < maps[index].arcIndex){
        if (maps[index].arc[i]->positionX() == x && maps[index].arc[i]->positionY() == y) {
            maps[index].arc[i]->decreaseLife(damage);
            flag=true;
        }
        i++;
    }
}

void mapList::checkSicario(int x, int y, int damage) {
    bool flag = false;
    int i=0;
    while (!flag && i < maps[index].sicIndex){
        if (maps[index].sic[i]->positionX() == x && maps[index].sic[i]->positionY() == y) {
            maps[index].sic[i]->decreaseLife(damage);
            flag=true;
        }
        i++;
    }
}

map mapList::getMap()
{
    map m = maps[index];
    return m;
}

void mapList::addArch( int life, int damage, int x, int y, int value)
{
    if (maps[index].arcIndex < N_ENEM)
    {
        while(mvwinch(getWin(), y, x) != ' ')
        {
             y = rand() % 20;
             x = rand() + 5 % 100;
        }
        maps[index].arc[maps[index].arcIndex] = new Arciere(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].arcIndex++;
    }
    else addGob(life * 3, damage / 2, x, y, value);
}



void mapList::addGob(int life, int damage, int x, int y, int value)
{
    if (maps[index].gobIndex < N_ENEM)
    {
        while(mvwinch(getWin(), y, x) != ' ')
        {
            y = rand() % 20;
            x= rand() + 5 % 100;
        }
        maps[index].gob[maps[index].gobIndex] = new Goblin(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].gobIndex++;
    }
    else addSic(life / 2, damage + 4, x, y, value);
}

void mapList::addSic(int life, int damage, int x, int y, int value)
{
    if (maps[index].sicIndex < N_ENEM)
    {
        while(mvwinch(getWin(), y, x) != ' ')
        {
            y = rand() % 20;
            x= rand() + 5 % 100;
        }
        maps[index].sic[maps[index].sicIndex] = new Sicario(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].sicIndex++;
    }
    else addArch(life, damage * 2, x, y, value);
}

mapList::mapList(int n, int index, Protagonista *p)
{
    this->n = n;
    this->index = index;
    this->mainCh = p;

    this->max_n = START_MAP_ARRAY_LEN;
    this->maps = new map[START_MAP_ARRAY_LEN];
}


WINDOW *mapList::getWin() {
    return maps[index].win;
}

mapList::mapList() {
    this->n = 0;
    this->index = 0;
    this->mainCh = nullptr;

    this->max_n = 0;
    this->maps = nullptr;
}

mapList::mapList(Protagonista *p) {
    this->n = 0;
    this->index = 0;
    this->mainCh = p;

    this->max_n = START_MAP_ARRAY_LEN;
    this->maps = new map[START_MAP_ARRAY_LEN];
}

map::map(int maptype) {
    this->mapType = maptype;
    init_win();
    this->arcIndex = 0;
    this->gobIndex = 0;
    this->sicIndex = 0;
}

void map::init_win() {
    WINDOW* win = newwin(MAP_YMAX, MAP_XMAX, 0, 0);
    this->win = win;
    draw_map();
}

map::map() {
    this->win = nullptr;
    this->arcIndex = 0;
    this->gobIndex = 0;
    this->sicIndex = 0;
}

void map::draw_map() {
    for (int i = 0; i < MAP_YMAX; i++) {
        mvwprintw(win, i, 0, "%s", maps[this->mapType][i]);
        box(win, 0, 0);
    }
}

int mapList::getGobNumber()
{
    return maps[index].gobIndex;
}

void mapList::addEnemies() {
    int diff = mainCh->getDifficulty();
    int type = maps[index].mapType;
    addGob(diff*10, diff*5, rand() % 100, rand() % 20, diff);
    addSic(diff*3, diff*3, rand() % 100, rand() % 20, diff + 2);
    addArch(diff * 2 + 5, diff * 7, rand() % 100, rand() % 20, diff*2);
    for (int i = 0; i < diff; ++i)
    {
        int choice = rand() % 3;
        if (choice == 0)
        {
            addGob(diff*10, diff*5, rand() % 100, rand() % 20, diff);
        }
        else if (choice == 1)
        {
            addSic(diff*3, diff*3, rand() % 100, rand() % 20, diff + 2);
        }
        else
        {
            addArch(diff * 2 + 5, diff * 7, rand() % 100, rand() % 20, diff*2);
        }
    }
}

int mapList::getN() {
    return n;
}

int mapList::getIndex() {
    return index;
}

map *mapList::getMaps() {
    return maps;
}

void mapList::setIndex(int index) {
    this->index = index;
}

bool mapList::hasNext() {
    if (index < n-1) return true;
    else return false;
}

bool mapList::hasPrev() {
    if (index > 0) return true;
    else return false;
}

void mapList::setN(int n){
    this->n = n;
}

void mapList::setNewGame() {
    setN(0);
    setIndex(-1);
}

void mapList::restoreArch(int life, int damage, int x, int y, int value, int index)
{
    maps[index].arc[maps[index].arcIndex] = new Arciere(life, damage, maps[index].win, y, x, value, this->mainCh);
    maps[index].arcIndex++;
}

void mapList::restoreGob(int life, int damage, int x, int y, int value, int index) {
    maps[index].gob[maps[index].gobIndex] = new Goblin(life, damage, maps[index].win, y, x, value, this->mainCh);
    maps[index].gobIndex++;
}

void mapList::restoreSic(int life, int damage, int x, int y, int value, int index) {
    maps[index].sic[maps[index].sicIndex] = new Sicario(life, damage, maps[index].win, y, x, value, this->mainCh);
    maps[index].sicIndex++;
}

int mapList::getPrevType()
{
    if (index >= 0)
        return maps[index].mapType;
    return 0;
}

