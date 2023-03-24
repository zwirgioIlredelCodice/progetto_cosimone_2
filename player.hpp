//
// Created by marco on 18/03/2023.
//

#ifndef PROGETTO_COSIMONE_2_PLAYER_HPP
#define PROGETTO_COSIMONE_2_PLAYER_HPP


#include "strutture.h"

//  using namespace std;

class Protagonista
{
    public:
        Protagonista(WINDOW * win, int y, int x, char c, int life, int currency, weapon A[], int n);

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
        void shoot(); // 'c' to trigger

        // funzione per cambiare arma
        void changeWeapon();  // 's' to trigger

        //ritorna la posizione del protagonista nell'asse x
        int positionX();

        // ritorna la posizione nell' asse y
        int positionY();

        // ritorna il carattere del protagonista
        char retChar();


    protected:
        int life;
        int currency;
        int xLoc, yLoc, xMax, yMax;
        char character;
        WINDOW * curwin;
        weapon weapons[N_ARMI];
        int n_weap;
        int weap_index;

};


#endif //PROGETTO_COSIMONE_2_PLAYER_HPP
