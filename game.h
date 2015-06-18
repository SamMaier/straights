//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_GAME_H
#define STRAIGHTS_GAME_H


#include <vector>
#include "deck.h"
#include "Card.h"
#include "hand.h"
#include "table.h"
#include "Player.h"


class Game {
public:
    Game(int seed = 0);
    void run();
    static const int NUM_PLAYERS = 4;
private:
    void play(Card card);
    void discard(Card card);
    void disablePlayer();
    void exit();
    void nextTurn();
    void nextRound();
    int currentPlayer_;
    int currentRound_;
    Deck deck_;
    Table table_;
    std::vector<Hand> hands_;
    std::vector<int> scores_;
    std::vector<Player> players_;
    bool running_;

};


#endif //STRAIGHTS_GAME_H
