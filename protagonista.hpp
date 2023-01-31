#include <iostream>
#include <ncurses.h>

using namespace std;

#define N_ARMI 5   //numero massimo di armi, !!MODIFICARE!!

struct arma
{
    string nome;
    int danno;
    int portata;
};

class Protagonista
{
protected:
    int salute;
    int valuta;
    arma armi[N_ARMI];
    int n_armi;

public:
    Protagonista(int salute, int valuta, arma armi[], int n);

    // movimento e sparare

    //funzioni che riguardano l'iterazione con la mappa

    void subisci_danno(int danno);

    void aumenta_vita(int vita);

    void incrementa_valuta(int valuta);

    void decrementa_valuta(int valuta);

    void nuova_arma(arma nuova);

    void reset_consumabili();


};
