#include <iostream>
#include <ncurses.h>
#include "protagonista.hpp"

using namespace std;

int main() {
    initscr();
    noecho();

    int height, width, starty, startx;
    height = 20;
    width = 40;
    starty = startx = 10;

    WINDOW * trywin = newwin(height, width, starty, startx);
    refresh();
    box (trywin, 0, 0);

    wrefresh(trywin);

    mvprintw(30, 51, "life: %d", 100);
    mvprintw(31,51,"value: %d", 10);
    weapon A[1] = {
            "AAA", 10, 5,
    };
    Protagonista p = *new Protagonista(100, 0, A, 1, trywin, 1, 1, '@');

    while(1)
    {
        p.getmv();
        p.display();
    }

      // da sistemare


    getch();
    endwin();

    return 0;
}
