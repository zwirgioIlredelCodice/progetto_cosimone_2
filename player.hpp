//
// Created by marco on 18/03/2023.
//

#ifndef PROGETTO_COSIMONE_2_PLAYER_HPP
#define PROGETTO_COSIMONE_2_PLAYER_HPP


#include "strutture.h"
#include "mapList.hpp"

//  using namespace std;

struct map;

class mapList;

class Protagonista
{
    public:
        Protagonista();
        Protagonista(mapList* curMap, int y, int x, char c, int life, int currency, weapon A[], int n);

        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int getmv();
        void display();
        // decrementa la vita

        void decreaseLife(int damage);

        // incrementa la vita
        void increaseLife(int life);

        // incrementa la valuta
        void increaseCurrency(int currency);

        // decrementa la valuta
        void decreaseCurrency(int currency);

        // aggiunge una nuova arma all' array
        void newWeapon(weapon Weapon);

        // funzione per sparare
        void shot(); // 'c' to trigger

        // funzione per cambiare arma
        void changeWeapon();  // 's' to trigger

        //ritorna la posizione del protagonista nell'asse x
        int positionX();

        // ritorna la posizione nell' asse y
        int positionY();

        // ritorna il carattere del protagonista
        char retChar();

        /*
         * funzione che ritorna il danno attuale della sua arma
         */
        int retCurrentDamage();

        /*
         * funzione che ritorna la portata attuale dell'arma selezionata
         */
        int retCurrentScope();

        /*
         * funzione che ritorna la vita attuale
         */
        int getLife();

        /*
         * funzione che ritorna la valuta attuale
         */
        int getCurrency();

        /*
         * funzione che cambia la finestra in cui si trova il protagonista
         */


    protected:
        int life;
        int currency;
        int xLoc, yLoc, xMax, yMax;
        char character;
        mapList *listMap;
        weapon weapons[N_ARMI];
        int n_weap;
        int weap_index;

};


#endif //PROGETTO_COSIMONE_2_PLAYER_HPP
