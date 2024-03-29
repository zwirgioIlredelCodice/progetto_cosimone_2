//
// Created by fabione on 09/02/23.
//

#include "Salvataggio.hpp"

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
    if (head == nullptr) {
        head = newdata;
    } else {
        newdata->next = head;
        head = newdata;
    }
}


/*
 * Post condition: se non è presente un nodo con this->name == name allora ritorna ""
 */
string s_list::getvalue(string name) {
    s_data* t = head;
    string val = "";
    bool found = false;
    while (t != nullptr && !found) {
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

bool s_list::isin(string name) {
    if (this->getvalue(name) == "") {
        return false;
    } else {
        return true;
    }
}

void s_list::remove(string name) {
    s_data* t = head;

    if (t != nullptr) {
        if (t->name == name) {
            head = head->next;
            delete t;
        } else {
            bool isdel = false;
            while (t->next != nullptr && !isdel) {
                if (t->next->name == name) {
                    s_data* temp = t->next;
                    t->next = t->next->next;
                    delete temp; // free memory
                    isdel = true;
                }
                if (!isdel && t != nullptr) {
                    if (t->name == name) {
                        s_data* temp = t;
                        t = t->next;
                        delete temp; // free memory
                    }
                }
            }
        }
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

void s_list::free() {
    s_data* t = head;
    while (t != nullptr) {
        s_data* tocanc = t;
        t = t->next;
        delete tocanc; // free memory
    }
    head = nullptr;
}


Salvataggio::Salvataggio(Manager* manager, string namefile) {
    this->manager = manager;
    this->namefile = namefile;
}

string Salvataggio::get_string(string name) {
    return datalist.getvalue(name);
}

/*
 * Post condition: se non può essere convertito a un int ritorna std::invalid_argument
 */
int Salvataggio::get_int(string name) {
    return stoi(datalist.getvalue(name));
}

void Salvataggio::set_string(string name, string value) {
    if (datalist.isin(name)) {
        datalist.updatevalue(name, value);
    } else {
        datalist.insert(name, value);
    }
}

void Salvataggio::set_int(string name, int value) {
    string svalue = to_string(value);
    if (datalist.isin(name)) {
        datalist.updatevalue(name, svalue);
    } else {
        datalist.insert(name, svalue);
    }
}

void Salvataggio::load() {
    ifstream file;
    file.open(namefile); // apre il file in modalità lettura

    string name, value;
    if (file.is_open()) { // se esiste e si può leggere
        while (!file.eof()) {
            getline(file, name, '='); //mette in name i caratteri fino a = escluso
            getline(file, value);

            if (!name.empty() &&  !value.empty()) { // se è in un formato valido
                datalist.insert(name, value);
            }
        }
        file.close();
    }
};

void Salvataggio::save() {
    ofstream file;
    file.open(namefile); // apre il file in modalità scrittura

    if (file.is_open()) { // se esiste e si può leggere
        s_data *t = datalist.head;
        while (t != nullptr) {
            file << t->name << '=' << t->value << endl;
            t = t->next;
        }
        file.close();
    }
}

void Salvataggio::remove(string name) {
    datalist.remove(name);
}

void Salvataggio::set_protagonista() {
    Protagonista* p = &manager->protagonista;

    /*
     * salva gli attributi base
     */
    set_int("p_life", p->getLife());
    set_int("p_currency", p->getCurrency());
    set_int("p_x", p->positionX());
    set_int("p_y", p->positionY());
    set_int("p_n_weap", p->getN_weap());

    set_int("p_baseDamage", p->getBaseDamage());
    set_int("p_baseRange", p->getBaseRange());
    set_int("p_armor", p->getArmor());
    set_int("p_salesPercent", p->getSalesPercent());
    set_int("p_coinPercent", p->getCoinPercent());
    set_int("p_difficulty", p->getDifficulty());


    /*
     * salva le armi
     */
    int n_weap = p->getN_weap();
    weapon* weapons = p->getWeapons();
    for (int i = 0; i < n_weap; i++) {
        string basename = "weapons[" + to_string(i) + "]";
        set_string(basename + "name", weapons[i].name);
        set_int(basename + "damage", weapons[i].damage);
        set_int(basename + "scope", weapons[i].scope);
    }
}

void Salvataggio::get_protagonista() {
    /*
     * ripristina gli attributi base
     */
    int p_life = get_int("p_life");
    int p_currency = get_int("p_currency");
    int p_x = get_int("p_x");
    int p_y = get_int("p_y");
    int p_n_weap = get_int("p_n_weap");

    int p_baseDamage = get_int("p_baseDamage");
    int p_baseRange = get_int("p_baseRange");
    int p_armor = get_int("p_armor");
    int p_salesPercent = get_int("p_salesPercent");
    int p_coinPercent = get_int("p_coinPercent");
    int p_difficulty = get_int("p_difficulty");

    // crea un nuovo protagonista e rimpiazza il vecchio
    weapon* weapons = manager->protagonista.getWeapons();
    manager->protagonista = Protagonista(&manager->maps, p_y, p_x, '@', p_life, p_currency, p_baseDamage, p_baseRange,
                                         p_armor, p_salesPercent, p_coinPercent, p_difficulty, weapons, p_n_weap
    );

    /*
     * ripristina le armi
     */
    int n_weap = get_int("p_n_weap");
    for (int i = 0; i < n_weap; i++) {
        weapon w;
        string basename = "weapons[" + to_string(i) + "]";
        w.name = get_string(basename + "name");
        w.damage = get_int(basename + "damage");
        w.scope = get_int(basename + "scope");

        weapons[i] = w;
    }
}

void Salvataggio::set_mapList() {
    mapList* ml = manager->protagonista.getMapList();
    set_int("ml_n", ml->getN());
    set_int("ml_index", ml->getIndex());

    int ml_n = ml->getN();
    map* ma = ml->getMaps();
    for (int i = 0; i < ml_n; i++) {
        /*
         * salva le mappe
         */
        map m = ma[i];
        string basename = "maps[" + to_string(i) + "]";

        set_int(basename + "mapType", m.mapType);

        /*
         * salva i nemici
         */
        int archIndex = 0; // numero di arcieri vivi
        for (int j = 0; j < m.arcIndex; j++) {
            if (m.arc[j]->retAlive()) {
                string arcname = basename + "arch[" + to_string(archIndex) + "]";
                int life = m.arc[j]->retLife();
                set_int(arcname + "life", life);
                int damage = m.arc[j]->retCurrentDamage();
                set_int(arcname + "damage", damage);
                int yLoc = m.arc[j]->positionY();
                set_int(arcname + "yLoc", yLoc);
                int xLoc = m.arc[j]->positionX();
                set_int(arcname + "xLoc", xLoc);
                int value = m.arc[j]->retValue();
                set_int(arcname + "value", value);
                archIndex++;
            }
        }
        set_int(basename + "arcIndex", archIndex);

        int gobIndex = 0; // numero di goblin vivi
        for (int j = 0; j < m.gobIndex; j++) {
            if (m.gob[j]->retAlive()) {
                string gobname = basename + "gob[" + to_string(gobIndex) + "]";
                int life = m.gob[j]->retLife();
                set_int(gobname + "life", life);
                int damage = m.gob[j]->retDamage();
                set_int(gobname + "damage", damage);
                int yLoc = m.gob[j]->positionY();
                set_int(gobname + "yLoc", yLoc);
                int xLoc = m.gob[j]->positionX();
                set_int(gobname + "xLoc", xLoc);
                int value = m.gob[j]->retValue();
                set_int(gobname + "value", value);
                gobIndex++;
            }
        }
        set_int(basename + "gobIndex", gobIndex);

        int sicIndex = 0; // numero di sicari vivi
        for (int j = 0; j < m.sicIndex; j++) {
            if (m.sic[j]->retAlive()) {
                string sicname = basename + "sic[" + to_string(sicIndex) + "]";
                int life = m.sic[j]->retLife();
                set_int(sicname + "life", life);
                int damage = m.sic[j]->retCurrentDamage();
                set_int(sicname + "damage", damage);
                int yLoc = m.sic[j]->positionY();
                set_int(sicname + "yLoc", yLoc);
                int xLoc = m.sic[j]->positionX();
                set_int(sicname + "xLoc", xLoc);
                int value = m.sic[j]->retValue();
                set_int(sicname + "value", value);
                sicIndex++;
            }
        }
        set_int(basename + "sicIndex", sicIndex);
    }
}

void Salvataggio::get_mapList() {
    mapList* ml = &manager->maps;
    ml->clear();
    Protagonista* p = &manager->protagonista;

    int ml_index = get_int("ml_index");
    ml->setIndex(ml_index);

    int ml_n = get_int("ml_n");
    for (int i = 0; i < ml_n; i++) {
        /*
         * ripristina la mappa
         */
        map m;
        string basename = "maps[" + to_string(i) + "]";

        int mapType = get_int(basename + "mapType");
        int gobIndex = get_int(basename + "gobIndex");
        int arcIndex = get_int(basename + "arcIndex");
        int sicIndex = get_int(basename + "sicIndex");

        m = map(mapType); // crea una nuova mappa e la aggiunge
        ml->add(m);

        /*
         * ripristina i nemici
         */
        for (int j = 0; j < arcIndex; j++) {
            string arcname = basename + "arch[" + to_string(j) + "]";
            int life = get_int(arcname + "life");
            int damage = get_int(arcname + "damage");
            int yLoc = get_int(arcname + "yLoc");
            int xLoc = get_int(arcname + "xLoc");
            int value = get_int(arcname + "value");
            ml->restoreArch(life, damage, xLoc, yLoc, value); // aggiunge l'arciere
        }

        for (int j = 0; j < gobIndex; j++) {
            string gobname = basename + "gob[" + to_string(j) + "]";
            int life = get_int(gobname + "life");
            int damage = get_int(gobname + "damage");
            int yLoc = get_int(gobname + "yLoc");
            int xLoc = get_int(gobname + "xLoc");
            int value = get_int(gobname + "value");
            ml->restoreGob(life, damage, xLoc, yLoc, value); // aggiunge il goblin
        }

        for (int j = 0; j < sicIndex; j++) {
            string sicname = basename + "sic[" + to_string(j) + "]";
            int life = get_int(sicname + "life");
            int damage = get_int(sicname + "damage");
            int yLoc = get_int(sicname + "yLoc");
            int xLoc = get_int(sicname + "xLoc");
            int value = get_int(sicname + "value");
            ml->restoreSic(life, damage, xLoc, yLoc, value); // aggiunge il sicario
        }
    }

    p->setMapList(ml); // aggiorna le mappe del manager
}

void Salvataggio::save_gamestate() {
    deleteall();
    set_int("is_game_saved", 1);
    set_protagonista();
    set_mapList();

    save();
}

void Salvataggio::restore_gamestate() {
    load();

    get_protagonista();
    get_mapList();
}

void Salvataggio::deleteall() {
    datalist.free();

    ofstream file;
    file.open(namefile); // apre il file in modalità scrittura
    file.close();
}

Salvataggio::Salvataggio() {}

void Salvataggio::save_gameover() {
    deleteall();
    // Salvare le cose del personaggio tipo i Potenziamenti di velocità ... e monete
    Protagonista* p = &manager->protagonista;
    set_int("p_currency", p->getCurrency());
    set_int("p_n_weap", p->getN_weap());
    set_int("p_baseDamage", p->getBaseDamage());
    set_int("p_baseRange", p->getBaseRange());
    set_int("p_armor", p->getArmor());
    set_int("p_salesPercent", p->getSalesPercent());
    set_int("p_coinPercent", p->getCoinPercent());
    set_int("p_difficulty", p->getDifficulty());


    int n_weap = p->getN_weap();
    weapon* weapons = p->getWeapons();
    for (int i = 0; i < n_weap; i++) {
        string basename = "weapons[" + to_string(i) + "]";
        set_string(basename + "name", weapons[i].name);
        set_int(basename + "damage", weapons[i].damage);
        set_int(basename + "scope", weapons[i].scope);
    }
    save();
}

void Salvataggio::restore_newgame() {
    int p_currency = get_int("p_currency");
    int p_baseDamage = get_int("p_baseDamage");
    int p_baseRange = get_int("p_baseRange");
    int p_armor = get_int("p_armor");
    int p_salesPercent = get_int("p_salesPercent");
    int p_coinPercent = get_int("p_coinPercent");
    int p_difficulty = get_int("p_difficulty");

    int n_weap = get_int("p_n_weap");
    manager->protagonista = Protagonista(&manager->maps, 1, 1, '@', 100, p_currency, p_baseDamage, p_baseRange, p_armor,
                                         p_salesPercent, p_coinPercent, p_difficulty, manager->weapon_array, n_weap);
    weapon* weapons = manager->protagonista.getWeapons();
    for (int i = 0; i < n_weap; i++) {
        weapon w;
        string basename = "weapons[" + to_string(i) + "]";
        w.name = get_string(basename + "name");
        w.damage = get_int(basename + "damage");
        w.scope = get_int(basename + "scope");

        weapons[i] = w;
    }
}

bool Salvataggio::is_game_saved() {
    if (empty()) return false;
    else {
        if (datalist.isin("is_game_saved")) return true; // controlla se è salvato in memoria
        else {
            load();
            if (datalist.isin("is_game_saved")) return true; // controlla se è salvato sul file
            else return false;
        }
    }
}

bool Salvataggio::empty() {
    ifstream file;
    file.open(namefile); // apre il file in modalità lettura

    if (file.is_open()) { // se esiste e si può leggere
        // controllo che non sia vuoto
        file.seekg(0, ios::end);
        if (file.tellg() == 0) return true;
        else return false;
    } else return true;
}
