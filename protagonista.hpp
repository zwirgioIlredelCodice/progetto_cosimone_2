
#include "strutture.h"

using namespace std;

class Protagonista
{
protected:
    int salute;
    int valuta;
    arma armi[N_ARMI];
    int n_armi;
    WINDOW * win;
    int yMax, xMax, yLoc, xLoc;
    char simbol; //carattere con cui viene mostrato il progtagonista

public:
    Protagonista(int salute, int valuta, arma armi[], int n, WINDOW * win, int yLoc, int xLoc, char simbol);

    // sparare

    //funzioni che riguardano l'iterazione con la mappa

    void subisci_danno(int danno);

    void aumenta_vita(int vita);

    void incrementa_valuta(int valuta);

    void decrementa_valuta(int valuta);

    void nuova_arma(arma nuova);

    void reset_consumabili();

    void mvup();

    void mvdown();

    void mvleft();

    void mvright();

    int getmv();

    void display();


};
