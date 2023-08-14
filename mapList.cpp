//
// Created by alice on 08/08/23.
//

#include "mapList.hpp"

void mapList::add(map m) {
        if (n < 10){
            maps[n] = m;
            n++;
        }
}

void mapList::remove(int mapIndex){
    for (int i=mapIndex; i<n; i++){
        maps[i] = maps[i+1];
    }
    if (index >= mapIndex)
        index --;

}
void mapList :: next(){
    if (index < n-1) index++;
};

void mapList::prev() {
    if (index > 0) index--;
}


