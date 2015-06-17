//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_GAME_H
#define STRAIGHTS_GAME_H


#include "deck.h"
#include "Card.h"
#include "hand.h"

class Game {
public:
    Game();
    void play(Card card);
    void discard(Card card);
    Deck getDeck();
    void disablePlayer();
    void exit();
private:
    void nextTurn();
    void nextRound();
    int currentPlayer;
    Hand hands[];
    int points[];

};


#endif //STRAIGHTS_GAME_H
