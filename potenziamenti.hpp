//
// Created by fabione on 3/17/23.
//

#ifndef PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
#define PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
#include "player.hpp"

enum effects {
    nothing,
    life,
    armor,
    damage,
    range,
    sales,
    coins,
    difficulty,
};

class potenziamenti {
protected:
    effects effect;
    Protagonista* protagonista;
    int val;
public:
    potenziamenti(Protagonista* p, effects effect, int val = 0);

    void apply();
    int get_val();
    effects get_effect();
    string to_string();
};


#endif //PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
