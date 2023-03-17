//
// Created by fabione on 3/17/23.
//

#include "potenziamenti.hpp"

potenziamenti::potenziamenti(Protagonista* p, effects effect, int val) {
    this->protagonista = p;
    this->effect = effect;
    this->val = val;
}

void potenziamenti::apply() {
    switch (effect) {
        case nothing:
            break;
        case life:
            protagonista->increaseLife(val);
            break;
        case damage:
            break;
        case range:
            break;
        case speed:
            break;
        default:
            break;
    }
}

void potenziamenti::remove() {
    switch (effect) {
        case nothing:
            break;
        case life:
            protagonista->decreaseLife(val);
            break;
        case damage:
            break;
        case range:
            break;
        case speed:
            break;
        default:
            break;
    }
}