//
// Created by fabione on 8/24/23.
//

#ifndef CHARACTER_ADVENTURE_MANAGER_HPP
#define CHARACTER_ADVENTURE_MANAGER_HPP

#include "Salvataggio.hpp"
#include "Negozio.hpp"


class Salvataggio; // per evitare il ciclo di dipendenze

/**
 * classe che si occupa di gestire le interazioni tra le varie
 * componenti del gioco come le mappe, il protagonista, il negozio e il salvataggio
 */
class Manager {
public:
    Protagonista protagonista; /** il giocatore giocabile dall'utente */
    mapList maps; /** le mappe di gioco */
    weapon weapon_array[10]; /** le armi del giocatore */
    Salvataggio* salvataggio; /** parte che si occupa dei salvataggi */
    bool in_game; /** true se c'è una partita in atto, false altrimenti */

    /**
     * costruttore della classe Manager, inizializza tutti i vari componenti di gioco
     */
    Manager();

    /**
     * si occupa di creare una finestra di ncurses dove l'utente può
     * interagire graficamente con il manager di gioco, ovvero può creare
     * una nuova partita, continuare la precedente, uscire dal gioco e cancellare
     * i salvataggi
     */
    void menu();

    /**
     * gioca una nuova partita
     */
    void new_game();

    /**
     * continua la partita corrente, la partita corrente può essere la partita
     * corrente iniziata nella corrente esecuzione del programma o una partita
     * salvata in una esecuzione precedente.
     */
    void resume();

    /**
     * setta correttamente il manager di gioco dopo la morte del giocatore
     */
    void gameover();

    /**
     * resetta il manager di gioco come se fosse la prima volta che venga
     * aperto il programma (cancella tutti i salvataggi)
     */
    void reset();

    /**
     * termina l'esecuzione del gioco salvando se necessario la partita corrente
     */
    void quit();

    /**
     * gioca graficamente la mappa dove si trova il giocatore aprendo una
     * finestra grafica di ncurses
     */
    void play_map();

    /**
     * passa il personaggio in una nuova mappa, ogni 3 mappe entra nel negozio
     */
    void new_room();

    /**
     * passa il giocatore alla mappa successiva, se non c'è una mappa successiva
     * ne crea una nuova con new_room()
     */
    void next_room();

    /**
     * passa il giocatore alla mappa precedente
     */
    void prev_room();
};

#endif //CHARACTER_ADVENTURE_MANAGER_HPP
