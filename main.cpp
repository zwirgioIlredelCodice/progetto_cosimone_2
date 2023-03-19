
#include "player.hpp"

using namespace std;

int main() {   // sto sperimanentando una roba
    initscr();
    noecho();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    weapon A[1] = {
            "AAA", 10, 5
    };

/*
    WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Protagonista *p = new Protagonista( playwin, 1, 1, '@');   //10, 10, A, 1,
    do {
        p->display();
        wrefresh(playwin);
    } while (p->getmv() != 'x');   // x per uscire

    endwin();*/

    WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Protagonista *p = new Protagonista(10, 10, A, 1, playwin, 1, 1, '@');
    do {
        p->display();
        wrefresh(playwin);
    } while (p->getmv() != 'x');   // x per uscire

    endwin();

    return 0;
}
