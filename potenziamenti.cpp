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

string potenziamenti::to_string() {
    string s = "";
    switch (effect) {
        case nothing:
            break;
        case life:
            s.append("vita");
            break;
        case damage:
            s.append("danno");
            break;
        case range:
            s.append("portata");
            break;
        case speed:
            s.append("velocità");
            break;
        default:
            break;
    }
    s.append(", incremento: " + std::to_string(val));
    return s;
}
