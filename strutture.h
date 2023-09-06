
#ifndef CHARACTER_ADVENTURE_STRUTTURE_H
#define CHARACTER_ADVENTURE_STRUTTURE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <string>
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

#endif //CHARACTER_ADVENTURE_STRUTTURE_H
