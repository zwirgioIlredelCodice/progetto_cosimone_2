
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

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    Protagonista *p = new Protagonista(playwin, 1, 1, '@', 10, 10);
    do {
        p->display();
        wrefresh(playwin);
    } while (p->getmv() != 'x');   // x per uscire

    endwin();

    return 0;
}
