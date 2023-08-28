//
// Created by marco on 04/05/23.
//



#ifndef PROGETTO_COSIMONE_2_MAPLIST_HPP
#define PROGETTO_COSIMONE_2_MAPLIST_HPP

#include "nemici.hpp"
#include "strutture.h"

#define N_ENEM 10

using namespace std;

class Arciere;

class Goblin;

class Protagonista;

#define MAP_XMAX 20
#define MAP_YMAX 100

#define MAP_NUMBER 1

const char maps[MAP_NUMBER][MAP_XMAX][MAP_YMAX+1] = {
{
    "                                                                                                    ",
    "                                                                         |                          ",
    "                                                                         |                          ",
    "                                                                         |                          ",
    "                                                                         |                          ",
    "                                #######                                  |                          ",
    "                                #######                                                             ",
    "                                #######                                                             ",
    "                                #######                                                             ",
    "                                                                                                    ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
},
};

class map{
public:
    WINDOW *win;
    Arciere *arc[N_ENEM];
    int arcIndex;
    Goblin *gob[N_ENEM];
    int gobIndex;

    static WINDOW* init_win(int maptype);
    map();
    explicit map(int maptype);
};

class mapList {
protected:
    int n;  //capienza attuale array
    map maps[10];
    int index; //mappa attualmente selezionata
    Protagonista *mainCh;

public:
    mapList();
    mapList(Protagonista *p);
    mapList(int n, int index, Protagonista *p);


    /*
     * funzioni di base oer il movimento all'interno dell'array
     */

    void add(map m); //aggiunge in coda

    void remove(int mapIndex);

    void next();

    void prev();

    /*
     * funzione che "gioca" la mappa
     */
    void play();

    /*
    * effettuano il danno ai nemici nella posizione data
    */
    void checkGoblin(int x, int y, int damage);

    void checkArciere(int x, int y, int damage);

    map getMap();
    WINDOW* getWin();

    void addArch( int life, int damage, int x, int y, int value);

    void addGob( int life, int damage, int x, int y, int value);

    int getGobNumber();

    void addEnemys();

    int getN();
    int getIndex();
    map* getMaps();

};

#endif //PROGETTO_COSIMONE_2_MAPLIST_HPP
