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

struct map{
    map();

    WINDOW *win;
    Arciere *arc[N_ENEM];
    int arcIndex;
    Goblin *gob[N_ENEM];
    int gobIndex;
};

class mapList {
protected:
    int n;  //capienza attuale array
    map maps[10];
    int index; //mappa attualmente selezionata
    Protagonista *mainCh;

public:

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


};

/*
WINDOW * win = newwin(10,5,10,5);

mvwprintw(win, 10, 10, '|');

map one = {
        win
};

mapList* listaMappe = new mapList();

listaMappe->add(one);
 */




#endif //PROGETTO_COSIMONE_2_MAPLIST_HPP
