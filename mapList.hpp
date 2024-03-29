//
// Created by marco on 04/05/23.
//



#ifndef CHARACTER_ADVENTURE_MAPLIST_HPP
#define CHARACTER_ADVENTURE_MAPLIST_HPP

#include "nemici.hpp"

#define N_ENEM 15

using namespace std;

class Arciere;

class Goblin;

class Sicario;

class Protagonista;

#define MAP_YMAX 20
#define MAP_XMAX 100

#define MAP_NUMBER 5 //capienza maps



const char maps[MAP_NUMBER][MAP_YMAX][MAP_XMAX+1] = {
{
    "                  ]               $                         .                                      ",
    "                                                                                                   ",
    "             =======                  WATER~WATER~WATER                  |                         ",
    "               =====                                                     |                         ",
    "                  ==                .                                    |      .                  ",
    "                                                                         |                         ",
    "                                                                                                   ",
    "              .                              .              <>                                     ",
    "                                                                                                   ",
    "                 $                                                                                 ",
    "                                           ==                                        [             ",
    "          .                               =====                      .                             ",
    "               <>                        =======                                         $         ",
    "      ]                                                                                            ",
    "                                                                                                   ",
    "                   |                        .    $                   WATER                     .   ",
    "                   |                                                                               ",
    "                   |         .                                                                     ",
    "                                                                                  $                ",
    "                                                                        .                          ",
},
{
        "                                                                                                   ",
        "                 WATER~WATER~WATER                                                                 ",
        "              WATER~WATER~WATER~WATER                                              <>              ",
        "              $  WATER~WATER~WATER                               .                                 ",
        "     .                                                                                             ",
        "                                            $                            .                         ",
        "                                        .                                                          ",
        "               <>                                                                            [     ",
        "                                                                                                   ",
        "                                                          |                                        ",
        "                                                            |                                      ",
        "                                                          |   $        <>                  .       ",
        "            .                     $                         |                                      ",
        "                                                         |                                         ",
        "                   $                                                                               ",
        "   ]                                                                  .                            ",
        "                                                                           $                       ",
        "       ====                                                                                        ",
        "       ===                                                                                         ",
        "       ==                                                                                          ",
},
{
        "                                                                                                    ",
        "         WATER~WATER~WATER                         ==                      ]                        ",
        "                                .                  ======                              <>           ",
        "                                                       ==                                           ",
        "              .                                                     .                               ",
        "                                                                                  $                 ",
        "                                        WATER~WATER~WATER                                           ",
        "                  <>                       WATER~WATER                                              ",
        "                                                     $                          .                   ",
        "                                                                                                    ",
        "       $                                                                                            ",
        "                       .                                           |                                ",
        "                                                                   |                      .         ",
        "                                                                   |                                ",
        "           WATER~WATER~WATER                  .                                             [       ",
        "                                                                                                    ",
        "                        \\                                                         $                ",
        "                         \\ $                       <>                                               ",
        "                          \\                                                 .                      ",
        "                                                                                                    ",
},
{
        "         .                                                                                         ",
        "         WATER                            $                        $                               ",
        "                      =                                                                            ",
        "                     ===                                     <>                        /           ",
        "   .                =====                                                          WATER           ",
        "                   =======             .                                            /          $   ",
        "                                                                                                   ",
        "                                                                                                   ",
        "                                       WATER~WATER~WATER                               .           ",
        "             <>                                                                                    ",
        "               $                                                         =======                   ",
        "                                                                          =====                    ",
        "                                                             .             ===       [             ",
        "                WATER~WATER                                                 =                      ",
        "                                                                                                   ",
        "      ]                                                      \\                                    ",
        "                      .                                     WATER                                  ",
        "                                                       $        \\                                 ",
        "                                     <>                                                            ",
        "                                                                                      .            ",
},
{
        "                                                                     ====                          ",
        "                                     /                               . ==                          ",
        "           <>                     WATER                                 =                    [     ",
        "           .                       /                                                               ",
        "                                                              .                    $               ",
        "                         |                                    <>                \\                 ",
        "                         |                                                     WATER               ",
        "     $                   |                   WATER                                \\               ",
        "                                           $                                                       ",
        "                                                                                                   ",
        "                   WATER~WATER                                  . <>                               ",
        "                                                          .                       WATER~WATER      ",
        "                                                                                                   ",
        "   .    <>                                                                                         ",
        "                                                           <>               |                      ",
        "  ]                                                           $             |        .             ",
        "                            <>                                              |                      ",
        "    =                   .                   WATER                           |                      ",
        "    == .                                                                                           ",
        "    ====                                                                                           ",
}
};

class map{
public:
    WINDOW *win;
    Arciere *arc[N_ENEM];
    int arcIndex;
    Goblin *gob[N_ENEM];
    int gobIndex;
    Sicario *sic[N_ENEM];
    int sicIndex;
    int mapType;

    void draw_map();
    void init_win();
    map();
    map(int mapType);
};

#define START_MAP_ARRAY_LEN 10
class mapList {
protected:
    int n;  //capienza attuale array
    int max_n; // capienza array
    map* maps;  //  infinito
    int index; //mappa attualmente selezionata
    Protagonista *mainCh;



    void setN(int n);

public:
    mapList();

    mapList(Protagonista *p);
    mapList(int n, int index, Protagonista *p);


    /*
     * funzioni di base oer il movimento all'interno dell'array
     */

    void add(map m); //aggiunge in coda

    void clear();

    bool hasNext();
    void next();

    bool hasPrev();
    void prev();


    /*
    * effettuano il danno ai nemici nella posizione data
    */
    void checkGoblin(int x, int y, int damage);

    void checkArciere(int x, int y, int damage);

    void checkSicario(int x, int y, int damage);

    map getMap();
    WINDOW* getWin();

    void addArch( int life, int damage, int x, int y, int value);

    void restoreArch( int life, int damage, int x, int y, int value);

    void addGob( int life, int damage, int x, int y, int value);

    void restoreGob( int life, int damage, int x, int y, int value);

    void addSic( int life, int damage, int x, int y, int value);

    void restoreSic( int life, int damage, int x, int y, int value);

    int getGobNumber();

    void addEnemies();

    int getN();
    int getIndex();
    map* getMaps();

    void setNewGame();
    void setIndex(int index);

    int getPrevType();
};

//void fillWwin ();
//void fillWobstacles ();

#endif //CHARACTER_ADVENTURE_MAPLIST_HPP
