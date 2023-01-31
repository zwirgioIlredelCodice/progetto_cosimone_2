#include "protagonista.hpp"

Protagonista::Protagonista(int salute, int valuta, arma armi[], int n)
{
    this->salute = salute;
    this->valuta = valuta;
    if (n > N_ARMI)
        this->n_armi = N_ARMI;
    else
        this->n_armi = n;
    for (int i = 0; i < this->n_armi; i++)
    {
        this->armi[i].nome = armi[i].nome;
        this->armi[i].danno = armi[i].danno;
        this->armi[i].portata = armi[i].portata;
    }
}

void Protagonista::subisci_danno(int danno)
{
    this->salute -= danno;
}

void Protagonista::aumenta_vita(int vita)
{
    this->salute += vita;
}

void Protagonista::incrementa_valuta(int valuta)
{
    this->valuta += valuta;
}

void Protagonista::decrementa_valuta(int valuta)
{
    this->valuta -= valuta;
}

void Protagonista::nuova_arma(arma nuova)
{
    if (this->n_armi < N_ARMI)
    {
        this->armi[n_armi].nome = nuova.nome;
        this->armi[n_armi].danno = nuova.danno;
        this->armi[n_armi].portata = nuova.portata;
    }
    this->n_armi++;
}

void Protagonista::reset_consumabili()
{
    // i potenziamenti devono essere registrati in modo tale da poter eliminare i consumabili
    // ogni volta che si esce dalla partita
}