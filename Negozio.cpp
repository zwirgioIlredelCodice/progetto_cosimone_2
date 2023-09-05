//
// Created by fabione on 8/21/23.
//
#include <cstdlib>
#include <ncurses.h>
#include "Negozio.hpp"
#include "strutture.h"

itemPotenziamenti::itemPotenziamenti(Potenziamenti potenziamento, int cost) {
    this->potenziamento = potenziamento;
    this->cost = cost;
    this->can_buy = true;
}

itemPotenziamenti::itemPotenziamenti(){};

itemWeapon::itemWeapon(weapon wp, int cost) {
    this->wp = wp;
    this->cost = cost;
    this->can_buy = true;
}

itemWeapon::itemWeapon(){};

Negozio::Negozio(Protagonista *protagonista) {
    this->protagonista = protagonista;
    this->pdifficulty = protagonista->getDifficulty();

    /*
     * inizializzo tutti i possibili potenziamenti acquistabili
     */
    pot_choices[0] = itemPotenziamenti(Potenziamenti(protagonista, life, 25), 10);
    pot_choices[1] = itemPotenziamenti(Potenziamenti(protagonista, damage, 5), 15);
    pot_choices[2] = itemPotenziamenti(Potenziamenti(protagonista, range, 5), 15);
    pot_choices[3] = itemPotenziamenti(Potenziamenti(protagonista, armor, 2), 20);
    pot_choices[4] = itemPotenziamenti(Potenziamenti(protagonista, sales, 10), 25);
    pot_choices[5] = itemPotenziamenti(Potenziamenti(protagonista, coins, 10), 30);
    pot_choices[6] = itemPotenziamenti(Potenziamenti(protagonista, difficulty, -2), 40);

    /*
     * inizializzo tutte le possibili armi acquistabili
     */
    weapon_choices[0] = itemWeapon((weapon){"bow", 5, 10}, 20);
    weapon_choices[1] = itemWeapon((weapon){"sword", 10, 2}, 18);
    weapon_choices[2] = itemWeapon((weapon){"fist", 15, 1}, 25);
    weapon_choices[3] = itemWeapon((weapon){"crossbow", 7, 20}, 30);
    weapon_choices[4] = itemWeapon((weapon){"dagger", 20, 1}, 35);

    populate_negozio();
}

void Negozio::populate_negozio() {
    for (int i = 0; i < NEGOZIO_POTENZIAMENTI; i++) {
        int random = rand() % NEGOZIO_POTENZIAMENTI; // decide un potenziamento random tra tutti i disponibili

        pot_arr[i] = adjustDifficultyPot(pot_choices[random]); // lo bilancio

        // lo rappresento come una stringa
        pot_arr_s[i] = pot_arr[i].potenziamento.to_string();
        pot_arr_s[i].append(", " + to_string(pot_arr[i].cost) + "$");
    }
    for (int i = 0; i < NEGOZIO_WEAPON; i++) {
        int random = rand() % NEGOZIO_WEAPON; // decide un'arma random tra tutte le disponibili

        weapon_arr[i] = adjustDifficultyWeapon(weapon_choices[random]); // la bilancio

        // la rappresento come una stringa
        weapon_arr_s[i] = weapon_arr[i].wp.name + ", damage:" + to_string(weapon_arr[i].wp.damage) + ", raggio:" +
                to_string(weapon_arr[i].wp.scope) + ", " + to_string(weapon_arr[i].cost) + "$";
    }
}

bool Negozio::buy_potenziamento(int index) {
    itemPotenziamenti p = pot_arr[index];
    if (protagonista->getCurrency() >= p.cost && p.can_buy) { // se il protagonista ha abbastanza monete e non è già stato comprato
        protagonista->decreaseCurrency(p.cost);
        p.can_buy = false;
        p.potenziamento.apply(); // applica il potenziamento comprato al personaggio
        return true;
    } else return false;
}

bool Negozio::buy_weapon(int index) {
    itemWeapon w = weapon_arr[index];
    if (protagonista->getCurrency() >= w.cost && w.can_buy) { // se il protagonista ha abbastanza monete e non è già stato comprata
        protagonista->decreaseCurrency(w.cost);
        w.can_buy = false;
        protagonista->newWeapon(w.wp); // aggiungi l'arma comprata al personaggio
        return true;
    } else return false;
}

void Negozio::room_enter() {
    initscr(); // entra in curse mode
    noecho();
    cbreak();

    clear();

    int x_max, y_max;
    getmaxyx(stdscr, x_max, y_max);

    WINDOW* menuwin = newwin(x_max, y_max, 0, 0);
    box(menuwin, 0, 0);
    mvwprintw(menuwin, 0, 0, "NEGOZIO");
    mvwprintw(menuwin, x_max - 2, 1, "premi spazio per comprare, q per uscire");
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true); // abilita le frecce


    int choice, highlight = 0;

    const int pot_entry = NEGOZIO_POTENZIAMENTI;
    const int wp_entry  = NEGOZIO_WEAPON;
    const int menu_entry = pot_entry + wp_entry;
    
    const int menu_space = 3; // righe di spazio

    bool quit = false;
    while(!quit) {
        for (int i = 0; i < menu_entry; i++) {
            /*
             * scrivo la lista di oggetti
             */
            if (i == highlight) wattron(menuwin, A_REVERSE);
            if (i < pot_entry) {
                if (pot_arr[i].can_buy) mvwprintw(menuwin, i+menu_space, 1, "%s", pot_arr_s[i].c_str());
                else mvwprintw(menuwin, i+menu_space, 1, "...");
            } else {
                if (weapon_arr[i - pot_entry].can_buy) mvwprintw(menuwin, i+menu_space, 1, "%s", weapon_arr_s[i - pot_entry].c_str());
                else mvwprintw(menuwin, i+menu_space, 1, "...");
            }
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
                if (highlight < pot_entry) {
                    if (!buy_potenziamento(highlight)) {
                        mvwprintw(menuwin, x_max - 3, 1, "monete insufficienti");
                    }
                } else {
                    if (!buy_weapon(highlight - pot_entry)) {
                        mvwprintw(menuwin, x_max - 3, 1, "monete insufficienti");
                    }
                }
                break;
            case 'q':
                quit = true;
                break;
            default:
                break;
        }
    }
    endwin();
}

itemPotenziamenti Negozio::adjustDifficultyPot(itemPotenziamenti ipot) {
    int cost = ipot.cost  + (ipot.cost / 100) * difficulty;
    int val = ipot.potenziamento.get_val();
    effects effect = ipot.potenziamento.get_effect();
    switch (effect) {
        case nothing:
            break;
        case life:
            val += pdifficulty * 10;
            break;
        case armor:
            val += pdifficulty * 5;
            break;
        case damage:
            val += pdifficulty * 2;
            break;
        case range:
            val += pdifficulty;
            break;
        case sales:
            val += pdifficulty;
            break;
        case coins:
            val += pdifficulty;
            break;
        case difficulty:
            val += pdifficulty / 2;
            break;
        default:
            break;
    }
    return itemPotenziamenti(Potenziamenti(protagonista, effect, val), cost); // ritorna il potenziamento in vendita bilanciato
}

itemWeapon Negozio::adjustDifficultyWeapon(itemWeapon iwp) {
    return itemWeapon((weapon){iwp.wp.name, iwp.wp.damage + pdifficulty * 2, iwp.wp.scope + pdifficulty / 2},
                      iwp.cost  + (iwp.cost / 100) * difficulty); // ritorna l'arma in vendita bilanciata
}
