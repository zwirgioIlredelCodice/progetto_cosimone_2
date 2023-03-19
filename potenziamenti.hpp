//
// Created by fabione on 3/17/23.
//

#ifndef PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
#define PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
#include "player.hpp"

enum effects {
    nothing,
    life,
    damage,
    range,
    speed
};

class potenziamenti {
protected:
    effects effect;
    Protagonista* protagonista;
    int val;
public:
    potenziamenti(Protagonista* p, effects effect, int val = 0);

    void apply();
    void remove();
};


#endif //PROGETTO_COSIMONE_2_POTENZIAMENTI_HPP
