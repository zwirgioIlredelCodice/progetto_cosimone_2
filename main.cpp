

#include "manager.hpp"

using namespace std;

int main() {
    manager gamenmanager;
    gamenmanager.menu();

    /*
    initscr();
    noecho();
    cbreak();
    curs_set(0);


    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    weapon A[2] = {
            "bow", 20, 100,
            "gun", 50, 20,
    };

    WINDOW * playwin = newwin(25, 50, 10, 10);
    nodelay(playwin, 1);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);

    // creo mapList
    mapList *MM;

    Protagonista *p = new Protagonista(MM, 1, 1, '@', 1000, 10, A, 2);

    MM = new mapList(0, 0, p);

    //creo mappa
    mvwprintw(playwin, 15, 15, "|");

    map M = createMap(playwin);

    // aggiungo mappa alla lista
    MM->add(M);

    //aggiungo nemici alla mappa

    MM->addArch(10, 20, 20, 40, 200);
    MM->addGob(100, 5, 20, 30, 40);




    mvwprintw(stdscr, 10, 60, "Key arrows to move, S-shooting, C-change weapon");
    mvwprintw(stdscr, 11, 60, "Ctrl C to close");


    endwin();

    return 0;*/
}
