//
// Created by fabione on 8/24/23.
//
#include <curses.h>
#include <cstdlib>
#include "manager.hpp"
#include "player.hpp"
#include "negozio.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

manager::manager()
    : protagonista()
    /*: protagonista(this->curMap, 1, 1, '@', 1000, 10, this->weapon_array, 2)*/ {
    srand(666123); // da cambiare
}

void manager::menu() {
    initscr();
    noecho();
    cbreak();

    int x_max, y_max;
    getmaxyx(stdscr, x_max, y_max);

    WINDOW* menuwin = newwin(x_max, y_max, 0, 0);
    box(menuwin, 0, 0);
    mvwprintw(menuwin, 0, 0, "MENU");
    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    string choices[MENU_ENTRY] = {"New game", "Resume", "Quit"};
    int choice, highlight = 0;

    bool quit = false;
    while(!quit) {
        for (int i = 0; i < MENU_ENTRY; i++) {
            if (i == highlight) wattron(menuwin, A_REVERSE);

            mvwprintw(menuwin, i+1, 1, "%s", choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight >= MENU_ENTRY) highlight = MENU_ENTRY - 1;
                break;
            case ' ': // backspace
                if (choices[highlight] == "New game") {
                    endwin();
                    new_game();
                }
                else if (choices[highlight] == "Resume") {
                    endwin();
                    resume();
                }
                else if (choices[highlight] == "Quit") {
                    quit = true;
                }
            case KEY_F(1):
                quit = true;
                break;
            default:
                break;
        }
    }
    endwin();
}

void manager::new_game() {
    // da cambiare
    negozio nego(&protagonista);
    nego.room_enter();
}

void manager::resume() {

}

void manager::next_room() {

}

void manager::prev_room() {

}
