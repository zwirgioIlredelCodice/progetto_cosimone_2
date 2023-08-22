//
// Created by fabione on 8/21/23.
//
#include <cstdlib>
#include "negozio.hpp"
#include "strutture.h"

itemPotenziamenti::itemPotenziamenti(potenziamenti potenziamento, int cost) {
    this->potenziamento = potenziamento;
    this->cost = cost;
    this->can_buy = true;
}

itemPotenziamenti::itemPotenziamenti(){};

itemWeapon::itemWeapon(weapon wp, int cost) {
    this->wp = wp;
    this->cost = cost;
    this->can_buy = true;
}

itemWeapon::itemWeapon(){};

negozio::negozio(Protagonista *protagonista) {
    this->protagonista = protagonista;
    populate_negozio();

    pot_choices[0] = itemPotenziamenti(potenziamenti(protagonista, life, 10), 10);
    pot_choices[1] = itemPotenziamenti(potenziamenti(protagonista, damage, 10), 10);
    pot_choices[2] = itemPotenziamenti(potenziamenti(protagonista, range, 10), 10);
    pot_choices[3] = itemPotenziamenti(potenziamenti(protagonista, speed, 10), 10);

    weapon_choices[0] = itemWeapon((weapon){"arco", 5, 10}, 20);
    weapon_choices[1] = itemWeapon((weapon){"spada", 10, 5}, 20);
}

void negozio::populate_negozio() {
    for (int i = 0; i < NEGOZIO_POTENZIAMENTI; i++) {
        int random = rand() % NEGOZIO_POTENZIAMENTI;
        pot_arr[i] = pot_choices[random];
    }
    for (int i = 0; i < NEGOZIO_WEAPON; i++) {
        int random = rand() % NEGOZIO_WEAPON;
        weapon_arr[i] = weapon_choices[random];
    }
}

bool negozio::buy_potenziamento(int index) {
    itemPotenziamenti p = pot_arr[index];
    if (protagonista->getCurrency() >= p.cost && p.can_buy) {
        protagonista->decreaseCurrency(p.cost);
        p.can_buy = false;
        p.potenziamento.apply();
        return true;
    } else return false;
}

bool negozio::buy_weapon(int index) {
    itemWeapon w = weapon_arr[index];
    if (protagonista->getCurrency() >= w.cost && w.can_buy) {
        protagonista->decreaseCurrency(w.cost);
        w.can_buy = false;
        protagonista->newWeapon(w.wp);
        return true;
    } else return false;
}
