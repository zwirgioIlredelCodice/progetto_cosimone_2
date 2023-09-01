//
// Created by fabione on 8/24/23.
//
#include <curses.h>
#include <cstdlib>
#include "Manager.hpp"
#include "player.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

Manager::Manager() {
    srand(time(nullptr)); // da cambiare
    weapon_array[0] = {"bow", 20, 30};
    maps = mapList(0, 0, &protagonista);
    protagonista = Protagonista(&maps, 1, 1, '@', 100, 0, 0, 0, 0, 0, 100, 0, weapon_array, 1);
    salvataggio = new Salvataggio(this, "saves.txt");
    in_game = false;
}

void Manager::menu() {
    initscr();
    noecho();
    cbreak();
    clear();
    int x_max, y_max;
    getmaxyx(stdscr, x_max, y_max);

    WINDOW* menuwin = newwin(x_max, y_max, 0, 0);
    box(menuwin, 0, 0);
    mvwprintw(menuwin, 0, 0, "MENU");
    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    string choices[] = {"New game", "Resume", "Delete saves", "Quit"};
    int menu_entry = sizeof(choices) / sizeof(choices[0]);
    int choice, highlight = 0;

    bool terminate = false;
    while(!terminate) {
        for (int i = 0; i < menu_entry; i++) {
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
                if (highlight >= menu_entry) highlight = menu_entry - 1;
                break;
            case ' ': // backspace
                if (choices[highlight] == "New game") {
                    new_game();
                    wclear(menuwin);
                    box(menuwin, 0, 0);
                    mvwprintw(menuwin, 0, 0, "MENU");
                    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
                }
                else if (choices[highlight] == "Resume") {
                    resume();
                    wclear(menuwin);
                    box(menuwin, 0, 0);
                    mvwprintw(menuwin, 0, 0, "MENU");
                    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
                }
                else if (choices[highlight] == "Delete saves") {
                    reset();
                }
                else if (choices[highlight] == "Quit") {
                    quit();
                    terminate = true;
                    endwin();
                    exit(0);
                }
            /*case KEY_F(1):
                quit = true;
                break;
            */
            default:
                break;
        }
    }
    endwin();
}

void Manager::new_game() {
    in_game = true;
    if (!salvataggio->empty()) {
        if (salvataggio->is_game_saved()) {
            salvataggio->save_gameover();
            salvataggio->restore_newgame();
        } else {
            salvataggio->restore_newgame();
        }
    }
    // da cambiare
    next_room();

    /*
     * DEVE
     * resettare tutto per cominciare una nuova partita
     * gestire quando si cambia mappa salvando robe
     * fare entrare nel Negozio quando richiesto
     */
}

void Manager::resume() {
    if (in_game) {
        in_game = true;
        play_map();
    } else if (salvataggio->is_game_saved()) {
        in_game = true;
        salvataggio->restore_gamestate();
        play_map();
    }
}

void Manager::next_room() {
    if (maps.hasNext()) {
        maps.next();
    } else {
        new_room();
    }

    play_map();
    /*
     * DEVE
     * salvare lo stato della stanza e passare a quella dopo ripristinandola come salvata
     * se non ci sono stanze dopo crea una stanza con new_room()
     * giocare la stanza
     */
}

void Manager::prev_room() {
    if (maps.hasPrev()) {
        maps.prev();
    }
}

void Manager::new_room() {
    /*
     * DEVE
     * decidere una stanza a caso e inizializzarla con tutti i nemici (influenzato dalla difficoltà)
     */
    if (protagonista.getDifficulty() % 3 == 0) {
        Negozio negozio(&protagonista);
        negozio.room_enter();
    }
    protagonista.changeDifficulty(+1);
    maps.add(map(0));
    maps.addEnemys();
}

void Manager::quit() {
    /*
     * DEVE
     * salvare lo stato del gioco e permettere la terminazione del programma
     */
    if (in_game) {
        salvataggio->save_gamestate();
    } else {
        salvataggio->save_gameover();
    }
}

void Manager::gameover() {
    salvataggio->save_gameover();
    in_game = false;
}

void Manager::play_map() {
    clear();
    WINDOW* playwin = maps.getWin();
    map thismap = maps.getMap();
    thismap.draw_map();

    clear();
    initscr();
    noecho();
    cbreak();
    keypad(playwin, true);
    curs_set(0);

    nodelay(playwin, true);
    refresh();
    wrefresh(playwin);

    auto startTime = chrono::steady_clock::now();

    int index = maps.getIndex();
    map* maps_array = maps.getMaps();

    do
    {

        if (protagonista.getmv() == 'm') {
            menu();
        }
        usleep(10000);

        //protagonista.getmv();

        for(int i = 0; i < maps_array[index].gobIndex; i++)
        {
            maps_array[index].gob[i]->display();
        }

        for(int i = 0; i < maps_array[index].arcIndex; i++)
        {
            maps_array[index].arc[i]->display();
        }

        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 20000 == 0)
        {
            for(int i = 0; i < maps_array[index].gobIndex; i++)
            {
                maps_array[index].gob[i]->getmv();
                maps_array[index].gob[i]->display();
            }
        }

        wrefresh(playwin);
        refresh();
    }
    while (true);  // termina con ctrl C

    endwin();
}

void Manager::reset() {
    in_game = false;
    salvataggio->deleteall();
}
