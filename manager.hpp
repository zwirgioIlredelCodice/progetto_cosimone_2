//
// Created by fabione on 8/24/23.
//

#ifndef PROGETTO_COSIMONE_2_MANAGER_HPP
#define PROGETTO_COSIMONE_2_MANAGER_HPP

#include "player.hpp"
#include "strutture.h"
#include "Salvataggio.hpp"

#define MENU_ENTRY 3
class Salvataggio;

class manager {
protected:
    // cose che servono al protagonista
public:
    Protagonista protagonista;
    mapList maps;
    weapon weapon_array[10];
    Salvataggio* salvataggio;

    manager();

    void menu();
    void new_game();
    void resume();
    void quit();

    void new_room();
    void next_room();
    void prev_room();
};

#endif //PROGETTO_COSIMONE_2_MANAGER_HPP
