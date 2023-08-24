//
// Created by alice on 08/08/23.
//

#include "mapList.hpp"



void mapList::add(map m) {
        if (n < 10){
            maps[n] = m;
            n++;
        }
}

void mapList::remove(int mapIndex){
    for (int i=mapIndex; i<n; i++){
        maps[i] = maps[i+1];
    }
    if (index >= mapIndex)
        index --;

}
void mapList :: next(){
    if (index < n-1) index++;

};

void mapList::prev() {
    if (index > 0) index--;

}

void mapList::play() {
}

void mapList::checkGoblin(int x, int y, int damage){
    bool flag = false;
    int i=0;
    while (!flag && i < maps[index].gobIndex){
        if (maps[index].gob[i]->positionX() == x && maps[index].gob[i]->positionY() == y) {
            maps[index].gob[i]->decreaseLife(damage);
            if (maps[index].gob[i]->retLife() <= 0) {
                maps[index].gob[i]->disappear();
                mainCh->increaseCurrency(maps[index].gob[i]->retValue());
            }
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
            if (maps[index].arc[i]->retLife() <= 0) {
                maps[index].arc[i]->disappear();
                mainCh->increaseCurrency(maps[index].arc[i]->retValue());
            }
            flag=true;
        }
        i++;
    }
}

map mapList::getMap()
{
    return maps[index];
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


map createMap(WINDOW* win)
{
    map M;
    M.win = win;
    // metto a 0 gli indici per dire che è vuoto
    M.arcIndex = 0;
    M.gobIndex = 0;
    return M;
}

mapList::mapList(int n, int index, Protagonista *p)
{
    this->n = n;
    this->index = index;
    this->mainCh = p;
}