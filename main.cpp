
#include "player.hpp"
#include "nemici.hpp"


using namespace std;

int main() {

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

    mapList* MM;

    Protagonista *p = new Protagonista(MM, 1, 1, '@', 1000, 10, A, 2);
    Goblin *g = new Goblin(30, 50, MM->getMap().win, 'g', 10, 40, 10, p);
    Arciere *a = new Arciere(20, A[0], MM->getMap().win, 20, 40, 'a', 10, p);
    mvwprintw(stdscr, 10, 60, "Key arrows to move, S-shooting, C-change weapon");
    mvwprintw(stdscr, 11, 60, "Ctrl C to close");
    auto startTime = chrono::steady_clock::now();
    usleep(1000000);
    do
    {
        p->display();
        g->display();
        a->display();

        int choice = p->getmv();
        if(choice == 's')
        {
           // g->checkDamage();
        }

        wrefresh(playwin);
        refresh();
        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 20000 == 0)
        {
            g->getmv();
            g->display();
            wrefresh(playwin);
        }

        g->display();
        wrefresh(playwin);
        refresh();

    }
    while (true);   // termina con ctrl C

    endwin();

    return 0;
}
