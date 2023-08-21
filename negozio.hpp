//
// Created by fabione on 8/21/23.
//

#ifndef PROGETTO_COSIMONE_2_NEGOZIO_HPP
#define PROGETTO_COSIMONE_2_NEGOZIO_HPP

#include "player.hpp"
#include "potenziamenti.hpp"
#include "strutture.h"

#define NEGOZIO_POT_CHOICE 4
#define NEGOZIO_WEAPON_CHOICE 2
#define NEGOZIO_POTENZIAMENTI 3
#define NEGOZIO_WEAPON 1

class itemPotenziamenti {
public:
    potenziamenti potenziamento = potenziamenti(nullptr, nothing);
    int cost;

    itemPotenziamenti(potenziamenti potenziamento, int cost);
    itemPotenziamenti();
};

class itemWeapon {
public:
    weapon wp;
    int cost;

    itemWeapon(weapon wp, int cost);
    itemWeapon();
};

class negozio {
protected:
    Protagonista* protagonista;
    itemPotenziamenti pot_arr[NEGOZIO_POTENZIAMENTI];
    itemWeapon weapon_arr[NEGOZIO_WEAPON];

    itemPotenziamenti pot_choices[NEGOZIO_POT_CHOICE];
    itemWeapon weapon_choices[NEGOZIO_WEAPON_CHOICE];
public:
    negozio(Protagonista* protagonista);

    void populate_negozio();
    bool buy_potenziamento(int index);
    bool buy_weapon(int index);
};

#endif //PROGETTO_COSIMONE_2_NEGOZIO_HPP
