
#ifndef PROGETTO_COSIMONE_2_STRUTTURE_H
#define PROGETTO_COSIMONE_2_STRUTTURE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

// file in cui mettere le strutture dati per essere usate in tutti i file
//include anche le librerie così da non doverle mettere in ogni file, basta includere questo file.



using namespace std;

#define N_ARMI 5   //numero massimo di armi, !!MODIFICARE!!

struct weapon
{
    string name;
    int damage;
    int scope;
};

#endif //PROGETTO_COSIMONE_2_STRUTTURE_H
