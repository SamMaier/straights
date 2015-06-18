//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_GAME_H
#define STRAIGHTS_GAME_H


#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include "Table.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "View.h"


class Game {
public:
    Game(int seed = 0, View* view = NULL);
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
    View* view_;

};


#endif //STRAIGHTS_GAME_H
