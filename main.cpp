
#include <future>
#include "player.hpp"
#include "nemici.hpp"


using namespace std;

int main() {   // sto sperimanentando una roba

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
    nodelay(playwin, 1);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);
    mvwaddch(playwin, 10, 40, '+');


    Protagonista *p = new Protagonista(playwin, 1, 1, '@', 1000, 10, A, 2);
    Goblin *g = new Goblin(30, 50, playwin, 'g', 10, 40, 10, p);
    do
    {
        p->display();
        g->display();
        p->getmv();
        wrefresh(playwin);
        g->getmv(); // problema: eseguire più operazioni di movimento contemporaneamnete
        p->getmv();
        wrefresh(playwin);
    }
    while (1);   // termina con ctrl C

    endwin();

    return 0;
}
