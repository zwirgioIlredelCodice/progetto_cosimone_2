//
// Created by fabione on 09/02/23.
//

#ifndef PROGETTO_COSIMONE_2_SALVATAGGIO_HPP
#define PROGETTO_COSIMONE_2_SALVATAGGIO_HPP

#include "player.hpp"
#include "Manager.hpp"

using namespace std;

class Manager; // per evitare il ciclo di dipendeze

/**
 * classe di supporto per il salvataggio che si occupa di creare
 * una lista che contiene una tupla nome variable e valore della
 * variabile
 */
class s_data {
public:
    string name;
    string value;
    s_data* next; /** cuntinuazione della lista */

    /**
     * costruttore della classe s_data
     * @param name nome della variabile da salvare
     * @param value valore della variabile da salvare
     */
    s_data(string name = "", string value = "");
};

/**
 * classe che si occupa della gestione della lista di variabili salvarte
 */
class s_list {
public:
    s_data* head; /** testa della lista di salvataggio */

    s_list();

    /**
     * metodo che si occupa della cancellazione della lista di salvataggio
     */
    void free();

    /**
     * inserisce una nuova variabile in testa alla lista di salvataggio
     * @param name nome della variabile da salvare
     * @param value valore della variabile da salvare
     */
    void insert(string name, string value);

    /**
     * @param name nome della variabile la quale si vuole il valore
     * @return il valore associato al nome, se non è presente ritorna una stringa vuota
     */
    string getvalue(string name);

    /**
     * aggiorna un valore nel salvataggio
     * se non è presennte la variabile nel salvataggio non fa niente
     * @param name nome della variabile da aggiornare
     * @param new_value il nuovo valore della variabile da salvare
     */
    void updatevalue(string name, string new_value);

    /**
     * controlla se una variabile è salvata
     * @param name nome della variabile da controllare
     * @return true se è presente una variabile salvata con name = name, false altrimenti
     */
    bool isin(string name);

    /**
     * rimuove una variabile dalla lista di salvataggio
     * @param name nome della variabile da cancellare
     */
    void remove(string name);

    /**
     * scrive la lista di salvataggio nell stdout per debugging
     */
    void print();
};

/**
 * classe che si occupa del salvataggio e di ripristinare dello stato del gioco
 */
class Salvataggio {
protected:
    s_list datalist; /** lista di tutte le variabili salvate*/
    string namefile; /** nome del file dove verranno salvati i dati */
    Manager* manager; /** puntatore alla classe Manager */
public:
    /**
     * costruttore di default
     */
    Salvataggio();
    // inizializza la classe saves sul file namefile
    /**
     * costruttore della classe Salvataggio
     * @param manager puntatore alla classe Manager
     * @param namefile nome del file dove verranno salvati i dati
     */
    Salvataggio(Manager* manager, string namefile);

    /**
     * legge il fine di salvataggio e carica i dati in memoria
     */
    void load();

    /**
     * scrive i dati nel file
     */
    void save();

    /**
     * cancella tutti i salvataggi dalla memoria e dal file
     */
    void deleteall();

    /**
     * controlla c'è qualcosa di salvato
     * @return true se non c'è niente di salvato, false altrimenti
     */
    bool empty();

    /**
     * controlla se c'è una partita salvata
     * @return true se c'è una partita salvata, false altrimenti
     */
    bool is_game_saved();

    /**
     * restituisce una il valore di una variabile salvata (string)
     * @param name nome della variabile da restituire
     * @return il valore associato al nome, se il nome non è presente ritorna una stringa vuota
     */
    string get_string(string name);

    /**
     * restituisce una il valore di una variabile salvata (int)
     * @param name nome della variabile da restituire
     * @return il valore associato al nome, se il nome non è presente ritorna invalid_argument exception
     */
    int get_int(string name);

    /**
     * salva una variabile, se è presente aggiorna il valore altrimenti la aggiunge
     * @param name nome della variabile da salvare
     * @param value valore della variabile da salvare
     */
    void set_string(string name, string value);

    /**
     * salva una variabile, se è presente aggiorna il valore altrimenti la aggiunge
     * @param name nome della variabile da salvare
     * @param value valore della variabile da salvare
     */
    void set_int(string name, int value);

    /**
     * rimuove una variabile dal salvataggio
     * @param name nome della variabile da rimuovere
     */
    void remove(string name);

    /**
     * salva lo stato del protagonista
     */
    void set_protagonista();

    /**
     * ripristina il personaggio dai dati salvati
     */
    void get_protagonista();

    /**
     * salva tutte le mappe del gioco corrente
     */
    void set_mapList();

    /**
     * ripristina le mappe di gioco dai dati salvati
     */
    void get_mapList();

    /**
     * salva lo stato del gioco (protagonista e mappe)
     */
    void save_gamestate();

    /**
     * ripristina lo stato del gioco dai dati salvati
     */
    void restore_gamestate();

    /**
     * salva lo stato del gioco dopo la morte del personaggio
     */
    // da chiamare quando il personaggio muore (salvare il personaggio)
    void save_gameover();

    /**
     * ripristina lo stato del gioco dopo la morte del personaggio
     */
    // da chiamare quando si comincia un nuovo gioco (inizializzare il personaggio)
    void restore_newgame();
};


#endif //PROGETTO_COSIMONE_2_SALVATAGGIO_HPP
