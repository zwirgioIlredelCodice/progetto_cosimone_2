//
// Created by marco on 18/03/2023.
//

#ifndef PROGETTO_COSIMONE_2_PLAYER_HPP
#define PROGETTO_COSIMONE_2_PLAYER_HPP


#include <ncurses.h>

class Player{
public:
    Player(WINDOW * win, int y, int x, char c);

    void mvup();
    void mvdown();
    void mvleft();
    void mvright();
    int getmv();
    void display();

protected:
    int xLoc, yLoc, xMax, yMax;
    char character;
    WINDOW * curwin;

};

Player::Player(WINDOW *win, int y, int x, char c) {
    curwin = win;
    xLoc = x;
    yLoc = y;
    getmaxyx(curwin, yMax, xMax);
    keypad(curwin, 1);
    character = c;
}

void Player::mvup() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Player::mvdown() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc++;
    if (yLoc > yMax-2)
        yLoc = yMax-2;
}

void Player::mvleft() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Player::mvright() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc++;
    if (xLoc > xMax-2)
        xLoc = xMax-2;
}

int Player::getmv(){
    int choice = wgetch(curwin);
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


void Player::display() {
    mvwaddch(curwin, yLoc, xLoc, character);
}

#endif //PROGETTO_COSIMONE_2_PLAYER_HPP
