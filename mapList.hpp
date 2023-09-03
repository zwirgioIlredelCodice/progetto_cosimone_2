//
// Created by marco on 04/05/23.
//



#ifndef PROGETTO_COSIMONE_2_MAPLIST_HPP
#define PROGETTO_COSIMONE_2_MAPLIST_HPP

#include "nemici.hpp"

#define N_ENEM 10

using namespace std;

class Arciere;

class Goblin;

class Protagonista;

#define MAP_YMAX 20
#define MAP_XMAX 100

#define MAP_NUMBER 5 //capienza maps




const char maps[MAP_NUMBER][MAP_YMAX][MAP_XMAX+1] = {
{
    "                                                            .                                      ",
    "                                                                                                   ",
    "             =======                                                     |                         ",
    "               =====                                                     |      .                  ",
    "                  ==                .                                    |      .                  ",
    "                                                                         |                         ",
    "                                                                                                   ",
    "              .                              .                                                     ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                                           ==                                                      ",
    "          .                               =====                      .                             ",
    "                                         =======                                                   ",
    "                                                                                                   ",
    "                                                                                                   ",
    "                   |                        .                                             .        ",
    "                   |                                                                               ",
    "                   |         .                                                                     ",
    "                                        .                                                          ",
    "                                                                        .                          ",
},
{
        "                                                                                                   ",
        "                 water~water~water                                                                 ",
        "              water~water~water~water                                                              ",
        "                 water~water~water                               .                                 ",
        "     .                                                                                             ",
        "                                                                                                   ",
        "                                        .                                                          ",
        "                                                                                                   ",
        "                                                                                                   ",
        "                                                          |                                        ",
        "                                                            |                                     ",
        "                                                          |                                .       ",
        "            .                                               |                                      ",
        "                                                         |                                         ",
        "                                                                                                   ",
        "                                                                      .                            ",
        "                                                                                                   ",
        "       ====                                                                                        ",
        "       ===                                                                                         ",
        "       ==                                                                                          ",
},
{
        "                                                                                                   ",
        "         water~water~water                         ==                                              ",
        "                                .                  ======                                          ",
        "                                                       ==                                          ",
        "              .                                                                                    ",
        "                                                                                                    ",
        "                                        water~water~water                                           ",
        "                                            water~water                                             ",
        "                                                                                .                   ",
        "                                                                                                    ",
        "                                                                                                    ",
        "                       .                                           |                                ",
        "                                                                   |                                ",
        "                                                                   |                                ",
        "           water~water~water                  .                                                     ",
        "                                                                                                    ",
        "                        \                                                                           ",
        "                         \                                                                          ",
        "                          \                                                  .                      ",
        "                                                                                                    ",
},
{
        "         .                                                                                         ",
        "         water                                                                                     ",
        "                      =                                                                            ",
        "                     ===                                     <>                        /           ",
        "   .                =====                                                          water           ",
        "                   =======             .                                            /              ",
        "                                                                                                   ",
        "                                                                                                   ",
        "                                       water~water~water                               .           ",
        "             <>                                                                                    ",
        "                                                                         =======                  ",
        "                                                                          =====                    ",
        "                                                             .             ===                     ",
        "                water~water                                                 =                      ",
        "                                                                                                   ",
        "                                                             \                                     ",
        "                      .                                     water                                  ",
        "                                                                \                                   ",
        "                                     <>                                                            ",
        "                                                                                      .            ",
},
{
        "                                                                     ====                          ",
        "                                     /                               . ==                          ",
        "           <>                     water                                      =                     ",
        "           .                       /                                                               ",
        "                                                              .                                    ",
        "                         |                                    <>                \                  ",
        "                         |                                                     water               ",
        "                         |                                                        \                ",
        "                                                                                                   ",
        "                                                                                                   ",
        "                   water~water                                  . <>                               ",
        "                                                          .                       water~water      ",
        "                                                                                                   ",
        "   .    <>                                                                                         ",
        "                                                                            |                      ",
        "                                                                            |                      ",
        "                            <>                                              |                      ",
        "    =                   .                   water                           |                      ",
        "    == .                                 water~water                                               ",
        "    ====                                                                                           ",
}
};

class map{
public:
    WINDOW *win;
    Arciere *arc[N_ENEM];
    int arcIndex;
    Goblin *gob[N_ENEM];
    int gobIndex;
    int mapType;

    void draw_map();
    void init_win();
    map();
    map(int mapType);
};

class mapList {
protected:
    int n;  //capienza attuale array
    map maps[10];  // da traformare in vector o comunque rendere infinito
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

    void clear();

    bool hasNext();
    void next();

    bool hasPrev();
    void prev();


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

    void setIndex(int index);
};

//void fillWwin ();
//void fillWobstacles ();

#endif //PROGETTO_COSIMONE_2_MAPLIST_HPP
