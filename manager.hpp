//
// Created by fabione on 8/24/23.
//

#ifndef PROGETTO_COSIMONE_2_MANAGER_HPP
#define PROGETTO_COSIMONE_2_MANAGER_HPP

#include "player.hpp"
#include "strutture.h"

#define MENU_ENTRY 3

class manager {
protected:
    Protagonista protagonista;
    // cose che servono al protagonista
    weapon weapon_array[10];
    mapList maps;
public:
    manager();


    void menu();
    void new_game();
    void resume();

    void next_room();
    void prev_room();
};

#endif //PROGETTO_COSIMONE_2_MANAGER_HPP
