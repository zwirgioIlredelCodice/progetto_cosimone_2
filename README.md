# CHARacter adventure
Progetto del corso di Programmazione dell'università di Bologna

## Dipendenze per la compilazione
Per la compilazione di questo progetto è richiesto `l'ide Clion` o i programmi `g++, cmake, make`.
Inoltre è consigliata l'installazione della libreria `ncurses`, nel caso in cui tale libreria non fosse
installata cmake dovrebbe installarla in automatico.

## Guida per la compilazione
### metodo 1 Clion
scaricare ed aprire il progetto col l'ide Clion, compilare il progetto normalmente

### metodo 2
* scaricare la cartella con i file sorgenti
* aprire il terminale nella directory del progetto
* eseguire `cmake .`
* eseguire `cmake --build .`

## Guida per l'esecuzione
* metodo 1
   * aprire il terminale dove è stato compilato il progetto, ovvero `CHARacter_adventure/cmake-build-release`
   * eseguire il programma `./CHARacter_adventure`
* metodo 2
   * aprire il terminale nella directory del progetto
   * eseguire il programma `./CHARacter_adventure`

Se vengono riscontrati eventuali malfunzionamenti del programma persistenti alla rieseguzione è
consigliato cancellare i salvataggi con l'apposita opzione `Delete all saves and reset the program` dal
menù di gioco.

## tasti utilizzati
* per il movimento del personaggio vengono utilizzati i tasti `freccia`
* per attaccare i nemici si utilizza la combinazione di tasti `w` `a` `s` `d` per sparare nelle rispettive direzioni
* per cambiare arma viene utilizzato il tasto `c`

