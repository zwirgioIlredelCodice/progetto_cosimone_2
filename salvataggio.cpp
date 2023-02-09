//
// Created by fabione on 09/02/23.
//

#include "salvataggio.hpp"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

s_data::s_data(string name, string value) {
    this->name = name;
    this->value = value;
    this->next = nullptr;
}

s_list::s_list() {
    head = nullptr;
}

void s_list::insert(string name, string value) {
    s_data* newdata = new s_data(name, value);
    s_data* t = head;
    if (head == nullptr) {
        head = newdata;
    } else {
        while (t->next != nullptr) {
            t = t->next;
        }
        t->next = newdata;
    }
}


/*
 * Post condition: se non è presente un nodo con this->name == name allora ritorna ""
 */
string s_list::getvalue(string name) {
    s_data* t = head;
    string val = "";
    bool found = false;
    while (t != nullptr || !found) {
        if (name == t->name) {
            val = t->value;
            found = true;
        }
        t = t->next;
    }
    return val;
}

/*
 * postcpndition: cambia il valore solo se è presente il nodo
 */
void s_list::updatevalue(string name, string new_value) {
    s_data* t = head;
    bool found = false;
    while (t != nullptr || !found) {
        if (name == t->name) {
            t->value = new_value;
            found = true;
        }
        t = t->next;
    }
}

void s_list::print() {
    s_data* t = head;
    cout << '[' << endl;
    while (t != nullptr) {
        cout << "n: " << t->name << " v: " << t->value << ',' << endl;
        t = t->next;
    }
    cout << ']' << endl;
}

salvataggio::salvataggio(string namefile) {
    this->namefile = namefile;
}

string salvataggio::get_string(string name) {
    return datalist.getvalue(name);
}

/*
 * Post condition: se non può essere convertito ad un int ritorna std::invalid_argument
 */
int salvataggio::get_int(string name) {
    return stoi(datalist.getvalue(name));
}

void salvataggio::add_string(string name, string value) {
    datalist.insert(name, value);
}

void salvataggio::add_int(string name, int value) {
    datalist.insert(name, to_string(value));
}

void salvataggio::update_string(string name, string value) {
    datalist.updatevalue(name, value);
}

void salvataggio::update_int(string name, int value) {
    datalist.updatevalue(name, to_string(value));
}

void salvataggio::load() {
    ifstream file;
    file.open(namefile); // apre il file in modalità lettura

    string name, value;
    if (file.is_open()) { // se esiste e si può leggere
        while (!file.eof()) {
            getline(file, name, '='); //mette in name i caratteri fino a = escluso
            getline(file, value);

            if (name != "" &&  value != "") { // se è in un formato valido
                datalist.insert(name, value);
            }
        }
        file.close();
    }
};

void salvataggio::save() {
    ofstream file;
    file.open(namefile); // apre il file in modalità scrittura

    if (file.is_open()) {
        s_data *t = datalist.head;
        while (t != nullptr) {
            file << t->name << '=' << t->value << endl;
            t = t->next;
        }
    }
}