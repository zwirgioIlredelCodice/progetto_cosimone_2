
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
            "bow", 100, 10,
            "gun", 200, 20,
    };

    WINDOW * playwin = newwin(25, 50, 10, 10);
    nodelay(playwin, 1);
    box(playwin, 0, 0);
    refresh();
    wrefresh(playwin);


    Protagonista *p = new Protagonista(playwin, 1, 1, '@', 1000, 10, A, 2);
    Goblin *g = new Goblin(30, 50, playwin, 'g', 10, 40, 10, p);
    auto startTime = chrono::steady_clock::now();
    usleep(1000000);
    do
    {
        p->display();
        g->display();

        p->getmv();

        wrefresh(playwin);

        if ((chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count() / 1000) % 2 == 0)
        {
            g->getmv(); // problema: viene eseguito un movimento di troppe caselle come se si muovess anche se non entre nell'if
            g->display();
            wrefresh(playwin);
        }

        wrefresh(playwin);

    }
    while (1);   // termina con ctrl C

    endwin();

    return 0;
}
