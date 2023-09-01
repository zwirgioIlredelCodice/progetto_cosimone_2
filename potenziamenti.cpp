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
        case armor:
            protagonista->increaseArmor(val);
            break;
        case damage:
            protagonista->increaseBaseDamage(val);
            break;
        case range:
            protagonista->increaseBaseRange(val);
            break;
        case sales:
            protagonista->increaseSalesPercent(val);
            break;
        case coins:
            protagonista->increaseCoinPercent(val);
            break;
        case difficulty:
            protagonista->changeDifficulty(val);
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
           s.append("life");
            break;
        case armor:
            s.append("armor");
            break;
        case damage:
            s.append("damage");
            break;
        case range:
            s.append("range");
            break;
        case sales:
            s.append("sales%");
            break;
        case coins:
            s.append("coins%");
            break;
        case difficulty:
            s.append("difficulty");
            break;
        default:
            break;
    }
    s.append(", increment: " + std::to_string(val));
    return s;
}

int potenziamenti::get_val() {
    return val;
}

effects potenziamenti::get_effect() {
    return effect;
}
