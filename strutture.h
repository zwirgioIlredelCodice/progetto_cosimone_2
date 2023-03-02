#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>

// file in cui mettere le strutture dati per essere usate in tutti i file
//include anche le librerie così da non doverle mettere in ogni file, basta includere questo



using namespace std;

#define N_ARMI 5   //numero massimo di armi, !!MODIFICARE!!

struct arma
{
    string nome;
    int danno;
    int portata;
};
