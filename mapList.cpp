//
// Created by alice on 08/08/23.
//

#include "mapList.hpp"



void mapList::add(map m) {
        if (n < 10){
            maps[n] = m;
            addEnemys();
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
void mapList::next(){
    if (index < n-1) index++;

};

void mapList::prev() {
    if (index > 0) index--;

}

void mapList::play() { // da implementare
    WINDOW* playwin = getWin();

    clear();
    initscr();
    noecho();
    cbreak();
    keypad(playwin, true);
    curs_set(0);

    nodelay(playwin, 1);
    refresh();
    wrefresh(playwin);

    auto startTime = chrono::steady_clock::now();

    do
    {
        mainCh->getmv();

        for(int i = 0; i < maps[index].gobIndex; i++)
        {
            maps[index].gob[i]->display();
            mainCh->getmv();
        }

        for(int i = 0; i < maps[index].arcIndex; i++)
        {
            maps[index].arc[i]->display();
        }

        wrefresh(playwin);

        mainCh->getmv();

        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 20000 == 0)
        {
            for(int i = 0; i < maps[index].gobIndex; i++)
            {
                maps[index].gob[i]->getmv();
                maps[index].gob[i]->display();
                wrefresh(playwin);
            }
        }

        wrefresh(playwin);
        refresh();
    }
    while (true);  // termina con ctrl C

    //
    while(wgetch(playwin) != ' ') {
        sleep(1);
    }
    endwin();
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
    this->win = init_win(maptype);
    this->arcIndex = 0;
    this->gobIndex = 0;
}

WINDOW* map::init_win(int maptype) {
    WINDOW* win = newwin(MAP_XMAX, MAP_YMAX, 0, 0);
    for (int i = 0; i < MAP_XMAX; i++) {
        mvwprintw(win, i, 0, "%s", maps[maptype][i]);
    }
    box(win, 0, 0);
    return win;
}

map::map() {
    this->win = nullptr;
    this->arcIndex = 0;
    this->gobIndex = 0;
}

int mapList::getGobNumber()
{
    return maps[index].gobIndex;
}

void mapList::addEnemys() {
    // da cambiare
    addArch(10, 10, 10, 2, 100);
    addGob(20, 5, 80, 15, 22);
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

