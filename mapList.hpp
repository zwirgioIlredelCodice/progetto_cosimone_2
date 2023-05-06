//
// Created by marco on 04/05/23.
//



#ifndef PROGETTO_COSIMONE_2_MAPLIST_HPP
#define PROGETTO_COSIMONE_2_MAPLIST_HPP

#include "nemici.hpp"

#define N_ENEM 10

using namespace std;

struct map
{
    WINDOW *win;
    Arciere arch[N_ENEM];
    Goblin gob[N_ENEM];
};

class mapList
{
protected:
    int n;
    map maps[10];
    int index;

    void resize(map *A, int l);

public:
    void add(map M);

    void remove(map M);

    void next




};

#endif //PROGETTO_COSIMONE_2_MAPLIST_HPP
