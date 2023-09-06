//
// Created by fabione on 3/17/23.
//

#ifndef CHARACTER_ADVENTURE_POTENZIAMENTI_HPP
#define CHARACTER_ADVENTURE_POTENZIAMENTI_HPP
#include "player.hpp"

/**
 * codice che contraddistingue la tipologia di potenziamento (effetto)
 */
enum effects {
    nothing,
    life,
    armor,
    damage,
    range,
    sales,
    coins,
    difficulty,
};

/**
 * Classe che si occupa di definire e applicare i Potenziamenti al protagonista
 */
class Potenziamenti {
protected:
    effects effect;
    Protagonista* protagonista;
    int val;
public:
    /**
     * Costruttore per la classe Potenziamenti
     * @param p puntatore alla classe Protagonista a cui verrà applicato il potenziamento
     * @param effect tipo di potenziamento
     * @param val valore del potenziamento (ad esempio 10 vita in più)
     */
    Potenziamenti(Protagonista* p, effects effect, int val = 0);

    /**
     * applica il potenziamento al protagonista
     */
    void apply();

    /**
     * @return (val) il valore del potenziamento
     */
    int get_val();

    /**
     * @return (effect) il l'effetto del potenziamento
     */
    effects get_effect();

    /**
     * @return la rappresentazione sotto forma di stringa del potenziamento
     */
    string to_string();
};


#endif //CHARACTER_ADVENTURE_POTENZIAMENTI_HPP
