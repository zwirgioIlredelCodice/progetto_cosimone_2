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

    void resize(map *A, int l)
    {
        map arr[l];
        for (int i = 0; i < l; ++i)
        {
            arr[i] = A[i];
        }
        A = arr;
    }

public:
    void add(map M)
    {
        if (n >= size(maps))
        {
            resize(maps, size(maps) * 2);
        }

        map[n] = M;
        n++;
        if (n == size(maps))
        {
            resize(maps, size(maps) * 2);
        }



    }


};

#endif //PROGETTO_COSIMONE_2_MAPLIST_HPP
