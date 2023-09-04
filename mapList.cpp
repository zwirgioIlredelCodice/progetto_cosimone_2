//
// Created by alice on 08/08/23.
//

#include "mapList.hpp"



void mapList::add(map m) {
    maps[n] = m;
    n++;
}

void mapList::remove(int mapIndex){
    for (int i=mapIndex; i<n; i++){
        maps[i] = maps[i+1];
    }
    if (index >= mapIndex)
        index --;

}

void mapList::clear() {
    n = 0;
    index = 0;
}

void mapList::next(){
    if (index < n-1) index++;

};

void mapList::prev() {
    if (index > 0) index--;

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
    if (maps[index].arcIndex < 10)
    {
        maps[index].arc[maps[index].arcIndex] = new Arciere(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].arcIndex++;
    }
}



void mapList::addGob(int life, int damage, int x, int y, int value)
{
    if (maps[index].gobIndex < 10)
    {
        maps[index].gob[maps[index].gobIndex] = new Goblin(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].gobIndex++;
    }
}

void mapList::addSic(int life, int damage, int x, int y, int value)
{
    if (maps[index].sicIndex < 10)
    {
        maps[index].sic[maps[index].sicIndex] = new Sicario(life, damage, maps[index].win, y, x, value, this->mainCh);
        maps[index].sicIndex++;
    }
}

mapList::mapList(int n, int index, Protagonista *p)
{
    this->n = n;
    this->index = index;
    this->mainCh = p;
}


WINDOW *mapList::getWin() {
    return maps[index].win;
}

mapList::mapList() {

}

mapList::mapList(Protagonista *p) {
    this->n = 0;
    this->index = 0;
    this->mainCh = p;
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

void mapList::addEnemys() {  // da fare basandosi sulla difficolta
    // da cambiare
    addArch(10, 10, 10, 2, 100);
    addGob(20, 5, 80, 15, 22);
    addSic(10, 5, 30, 6, 100);
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

/*
void fillWwin () {
    WINDOW * one = newwin (MAP_YMAX, MAP_XMAX, 0, 0);
    box(one, 0, 0);
    mapArr[0]=one;

    WINDOW * two = newwin (MAP_YMAX, MAP_XMAX, 0, 0);
    box(one, 0, 0);
    mapArr[1]=two;

    WINDOW * three = newwin (MAP_YMAX, MAP_XMAX, 0, 0);
    box(one, 0, 0);
    mapArr[2]=three;

    WINDOW * four = newwin (MAP_YMAX, MAP_XMAX, 0, 0);
    box(one, 0, 0);
    mapArr[3]=four;

    WINDOW * five = newwin (MAP_YMAX, MAP_XMAX, 0, 0);
    box(one, 0, 0);
    mapArr[4]=five;

    fillWobstacles();
}

void fillWobstacles () {
    mvwprintw(mapArr[0], 5, 5, "mud");
    //..., porta, $, vita
}
*/

