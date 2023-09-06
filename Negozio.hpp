//
// Created by fabione on 8/21/23.
//

#ifndef CHARACTER_ADVENTURE_NEGOZIO_HPP
#define CHARACTER_ADVENTURE_NEGOZIO_HPP

#include "Potenziamenti.hpp"
#include "strutture.h"

/**
 * numero di opzioni per i potenziamenti
 */
#define NEGOZIO_POT_CHOICE 7

/**
 * numero di opzioni per le armi
 */
#define NEGOZIO_WEAPON_CHOICE 5

/**
 * numero di opzioni per i potenziamenti visibili nel negozio
 */
#define NEGOZIO_POTENZIAMENTI 3

/**
 * numero di opzioni per le armi visibili nel negozio
 */
#define NEGOZIO_WEAPON 1

/**
 * classe di supporto per il negozio, contiene il potenziamento e il suo costo
 */
class itemPotenziamenti {
public:
    Potenziamenti potenziamento = Potenziamenti(nullptr, nothing); /** potenziamento da vendere*/
    int cost; /** costo del potenziamento */
    bool can_buy;

    itemPotenziamenti();

    /**
     * costruttore della classe itemPotenziamenti
     * @param potenziamento Potenziamento da vendere
     * @param cost costo del potenziamento
     */
    itemPotenziamenti(Potenziamenti potenziamento, int cost);
};

/**
 * classe di supporto per il negozio, contiene l'arma e il suo costo
 */
class itemWeapon {
public:
    weapon wp; /** arma da vender */
    int cost; /** costo dell'arma */
    bool can_buy;

    itemWeapon();

    /**
     * costruttore della classe itemWeapon
     * @param wp arma da vendere
     * @param cost costo dell'arma
     */
    itemWeapon(weapon wp, int cost);
};

/**
 * classe che si occupa di gestire il negozio di gioco
 */
class Negozio {
protected:
    Protagonista* protagonista; /** il protagonista che comprerà gli oggetti */
    int pdifficulty; /** difficoltà della partita */
    itemPotenziamenti pot_arr[NEGOZIO_POTENZIAMENTI]; /** array di potenziamenti in vendita nel negozio */
    itemWeapon weapon_arr[NEGOZIO_WEAPON]; /** array di armi in vendita nel negozio */
    string pot_arr_s[NEGOZIO_POTENZIAMENTI]; /** array di stringhe che rappresentano i potenziamenti in vendita nel negozio */
    string weapon_arr_s[NEGOZIO_WEAPON]; /** array di stringhe che rappresentano le armi in vendita nel negozio */

    itemPotenziamenti pot_choices[NEGOZIO_POT_CHOICE]; /** array  di tutti i potenziamenti che possono essere in vendita */
    itemWeapon weapon_choices[NEGOZIO_WEAPON_CHOICE]; /** array  di tutte li armi che possono essere in vendita */
public:

    /**
     * inizializza la classe Negozio
     * @param protagonista il protagonista che comprerà dal negozio
     */
    Negozio(Protagonista* protagonista);

    /**
     * bilancia il potenziamento in vendita rispetto alla difficoltà della partita
     * @param ipot potenziamento in vendita da bilanciare
     * @return il potenziamento il vendita bilanciato rispetto alla difficoltà della partita
     */
    itemPotenziamenti adjustDifficultyPot(itemPotenziamenti ipot);

    /**
     * bilancia l'arma in vendita rispetto alla difficoltà della partita
     * @param iwp arma in vendita da bilanciare
     * @return l'arma il vendita bilanciato rispetto alla difficoltà della partita
     */
    itemWeapon adjustDifficultyWeapon(itemWeapon iwp);

    /**
     * sceglie randomicamente i potenziamenti e le armi da mettere il vendita
     */
    void populate_negozio();

    /**
     * compra un potenziamento
     * @param index l'indice di pot_arr del potenziamento che si vuole comprare
     * @return true se il protagonista poteva comprare l'oggetto, false altrimenti
     */
    bool buy_potenziamento(int index);

    /**
     * compra un'arma
     * @param index l'indice di weapon_arr del potenziamento che si vuole comprare
     * @return true se il protagonista poteva comprare l'oggetto, false altrimenti
     */
    bool buy_weapon(int index);

    /**
     * entra nell'interfaccia grafica ncurses del negozio dove l'utente può comprare oggetti
     */
    void room_enter();
};

#endif //CHARACTER_ADVENTURE_NEGOZIO_HPP
