
#include "strutture.h"

using namespace std;

class Protagonista
{
protected:
    int life;
    int currency;
    arma weapons[N_ARMI];
    int n_weap;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol; //carattere con cui viene mostrato il progtagonista

public:
    Protagonista(int life, int currency, weapon weap[], int n, WINDOW * win, int yLoc, int xLoc, char simbol);

    // sparare

    //funzioni che riguardano l'iterazione con la mappa

    // decrementa la vita
    void decreaseLife(int damage);

    // incrementa la vita
    void increaseLife(int life);

    // incrementa la valuta
    void increaseCurrency(int currency);

    // decrementa la valuta
    void decreaseCurrency(int currency);

    // aggiunge una nuova arma
    void newWeapon(weapon Weapon);

    // resetta i potenziamenti temporanei
    void resetConsumable();

    // funzioni legate al movimento
    void mvup();

    void mvdown();

    void mvleft();

    void mvright();

    int getmv();

    void display();


};
