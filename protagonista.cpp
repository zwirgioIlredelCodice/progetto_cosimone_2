#include "protagonista.hpp"

Protagonista::Protagonista(int salute, int valuta, arma armi[], int n, WINDOW * win, int yLoc, int xLoc, char simbol)
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
    this->win = win;
    this->xLoc = xLoc;
    this->yLoc = yLoc;
    getmaxyx(win, this->yMax, this->xMax);
    this->simbol = simbol;
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

void Protagonista::mvup()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Protagonista::mvdown()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax-2)
        yLoc = yMax-2;
}

void Protagonista::mvleft()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Protagonista::mvright()
{
    mvwaddch(win, yLoc, xLoc, ' ');
    xLoc++;
    if (xLoc > xMax-2)
        xLoc = xMax-2;
}

int Protagonista::getmv()
{
    int choice = wgetch(win);
    switch (choice) {
        case KEY_UP:
            mvup();
            break;
        case KEY_DOWN:
            mvdown();
            break;
        case KEY_LEFT:
            mvleft();
            break;
        case KEY_RIGHT:
            mvright();
            break;
        default:
            break;
    }
    return choice;
}


void Protagonista::display()
{
    mvwaddch(win, yLoc, xLoc, simbol);
}