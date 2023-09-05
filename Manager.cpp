//
// Created by fabione on 8/24/23.
//
#include <curses.h>
#include <cstdlib>
#include "Manager.hpp"
#include "player.hpp"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

Manager::Manager() {
    srand(time(nullptr)); // setta il seme random diverso da ogni apertura del programma
    weapon_array[0] = {"bow", 20, 30};
    maps = mapList(0, 0, &protagonista);
    protagonista = Protagonista(&maps, 1, 1, '@', 1005, 0, 0, 0, 0, 0, 100, 0, weapon_array, 1);
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

    /*
     * scrive la finestra
     */
    box(menuwin, 0, 0);
    mvwprintw(menuwin, 0, 0, "MENU");
    mvwprintw(menuwin, x_max - 2, 1, "type space to select");

    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true); // abilita l'uso delle frecce

    string choices[] = {"New game", "Resume", "Delete saves", "Quit"};
    int menu_entry = sizeof(choices) / sizeof(choices[0]);
    int choice, highlight = 0;

    while(true) {
        for (int i = 0; i < menu_entry; i++) {

            /*
             * scrive il menu
             */
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
            case ' ':
                if (choices[highlight] == "New game") {
                    new_game();
                    wclear(menuwin);

                    // riscrivi la finestra
                    box(menuwin, 0, 0);
                    mvwprintw(menuwin, 0, 0, "MENU");
                    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
                }
                else if (choices[highlight] == "Resume") {
                    resume();
                    wclear(menuwin);

                    // riscrivi la finestra
                    box(menuwin, 0, 0);
                    mvwprintw(menuwin, 0, 0, "MENU");
                    mvwprintw(menuwin, x_max - 2, 1, "type space to select");
                }
                else if (choices[highlight] == "Delete saves") {
                    reset();
                }
                else if (choices[highlight] == "Quit") {
                    quit();
                    endwin();
                    exit(0); // termina il programma
                }
                break;
            default:
                break;
        }
    }
    endwin();
}

void Manager::new_game() {
    in_game = true;
  //  fillWwin();
    if (!salvataggio->empty()) { // se non è la prima volta che viene aperto il gioco
        if (salvataggio->is_game_saved()) { // se c'è una partita salvata
            // salva e carica la partita salvata come se fosse morto il personaggio
            salvataggio->save_gameover();
            salvataggio->restore_newgame();
        } else {
            // carica la partita salvata dopo che è morto il personaggio
            salvataggio->restore_newgame();
        }
    }

    maps.setNewGame();
    // entra nella prima mappa
    next_room();
}

void Manager::resume() {
    if (in_game) {
        in_game = true;
        play_map(); // riprende il gioco
    } else if (salvataggio->is_game_saved()) {
        in_game = true;
        salvataggio->restore_gamestate(); // carica l'ultima partita
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
}

void Manager::prev_room() {
    if (maps.hasPrev()) {
        maps.prev();
        play_map();
    }
}

void Manager::new_room() {
    /*
     * DEVE
     * decidere una stanza a caso e inizializzarla con tutti i nemici (influenzato dalla difficoltà)
     */
    if (protagonista.getDifficulty() % 3 == 0) { // ogni 3 stanze entra nel negozio prima di entrare in una nuova stanza
        Negozio negozio(&protagonista);
        negozio.room_enter();
    }
    protagonista.changeDifficulty(+1); // per ogni nuova stanza scoperta aumenta la difficoltà di 1
    int choice = rand();
    maps.add(map(choice % 5));  // scelta randomica della mappa a cui aggiungere poi i nemici
    maps.addEnemys();
    maps.next();
}

void Manager::quit() {
    if (in_game) {
        salvataggio->save_gamestate();
    } else { // se il giocatore è morto o non sono state iniziate nuove partite
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

    protagonista.goToStartPosition();

    do
    {
        if (protagonista.isDead()) {
            endwin();
            gameover();
        }
        int choice = protagonista.getmv();
        if (choice == 'm') {
            menu();
        }

        else if (mvwinch(playwin, protagonista.positionY() - 1, protagonista.positionX()) == '[' && choice == KEY_UP)
        {
            next_room();
            break;
        }
        else if (mvwinch(playwin, protagonista.positionY(), protagonista.positionX() + 1) == '[' && choice == KEY_RIGHT)
        {
            next_room();
            break;
        }
        else if (mvwinch(playwin, protagonista.positionY(), protagonista.positionX() - 1) == '[' && choice == KEY_LEFT)
        {
            next_room();
            break;
        }
        else if (mvwinch(playwin, protagonista.positionY() + 1, protagonista.positionX()) == '[' && choice == KEY_DOWN)
        {
            next_room();
            break;
        }
        if (maps.getIndex() > 0) {
            if (mvwinch(playwin, protagonista.positionY() - 1, protagonista.positionX()) == ']' && choice == KEY_UP)
            {
                prev_room();
                break;
            } else if (mvwinch(playwin, protagonista.positionY() + 1, protagonista.positionX()) == ']' && choice == KEY_DOWN)
            {
                prev_room();
                break;
            } else if (mvwinch(playwin, protagonista.positionY(), protagonista.positionX() - 1) == ']' && choice == KEY_LEFT)
            {
                prev_room();
                break;
            } else if (mvwinch(playwin, protagonista.positionY(), protagonista.positionX() + 1) == ']' && choice == KEY_RIGHT)
            {
                prev_room();
                break;
            }
        }


        //usleep(10000);

        //protagonista.getmv();

        for(int i = 0; i < maps_array[index].gobIndex; i++)
        {
            maps_array[index].gob[i]->display();
        }

        for(int i = 0; i < maps_array[index].arcIndex; i++)
        {
            maps_array[index].arc[i]->display();
        }

        for(int i = 0; i < maps_array[index].sicIndex; i++)
        {
            maps_array[index].sic[i]->display();
        }

        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 50000 == 0)
        {
            for(int i = 0; i < maps_array[index].gobIndex; i++)
            {
                maps_array[index].gob[i]->getmv();
                maps_array[index].gob[i]->display();
            }
        }

        if (chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - startTime).count() % 70000 == 0)
        {
            for(int i = 0; i < maps_array[index].sicIndex; i++)
            {
                maps_array[index].sic[i]->getmv();
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
