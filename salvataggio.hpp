//
// Created by fabione on 09/02/23.
//

#ifndef PROGETTO_COSIMONE_2_SALVATAGGIO_HPP
#define PROGETTO_COSIMONE_2_SALVATAGGIO_HPP

#include <string>
#include "player.hpp"
using namespace std;

#define REMOVE(var) remove(#var)
#define GET_INT(var) get_int(#var)
#define GET_STRING(var) get_string(#var)
#define SET_INT(var) set_int(#var, var)
#define SET_STRING(var) set_string(#var, var)

class s_data {
public:
    string name;
    string value;
    s_data* next;

    s_data(string name = "", string value = "");
};

/*
 * questa classe rappresenta una lista che a ogni nodo due stringhe, name e data
 */
class s_list {
public:
    s_data* head;

    // inizializza la lista
    s_list();

    // inserisce un nuovo nodo
    void insert(string name, string value);
    // data una stringa nome, ritorna il valore associato a quel nome
    string getvalue(string name);
    // data una stringa nome, aggiorna il valore associato a quel nome, se il nome non è presente non fà niente
    void updatevalue(string name, string new_value);
    // ritorna true se è presente un nodo con il name = name, false altrimenti
    bool isin(string name);
    // rimuove un elemento con name = name
    void remove(string name);
    // screive tutta la lista
    void print();
};

class salvataggio {
protected:
    s_list datalist;
    string namefile;
public:

    // inizializza la classe saves sul file namefile
    salvataggio(string namefile);

    // legge il file dei salvataggi e crea una lista con essi in modo da poterli leggere e scrivere
    void load();
    // scrive i salvataggi nel file
    void save();

    // data una stringa nome, ritorna il valore (stringa) associato a quel nome
    string get_string(string name);
    // data una stringa nome, ritorna il valore (int) associato a quel nome
    int get_int(string name);

    // inserisce o aggiorna un elemento a secondo se è presente o no
    void set_string(string name, string value);
    // inserisce o aggiorna un elemento a secondo se è presente o no
    void set_int(string name, int value);
    // rimuove un dato dal salvataggio
    void remove(string name);

    void set_protagonista(Protagonista* p);
    void get_protagonista(Protagonista* p);

};


#endif //PROGETTO_COSIMONE_2_SALVATAGGIO_HPP
