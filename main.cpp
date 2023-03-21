
#include "player.hpp"

using namespace std;

int main() {   // sto sperimanentando una roba


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

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    weapon A[2] = {
            "bow", 100, 10,
            "gun", 200, 20,
    };

    WINDOW * playwin = newwin(25, 50, 10, 10);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);
    mvwaddch(playwin, 10, 40, '+');

    Protagonista *p = new Protagonista(playwin, 1, 1, '@', 10, 10, A, 2);
    do {
        p->display();
        wrefresh(playwin);
    } while (p->getmv() != 'x');   // x per uscire

    endwin();

    return 0;
}
