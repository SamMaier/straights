//
// Created by Shiranka Miskin on 6/27/15.
//

#ifndef STRAIGHTS_GAMECONTROLLER_H
#define STRAIGHTS_GAMECONTROLLER_H


#include "Card.h"
#include "Game.h"

class GameController {
public:
    GameController(Game*);
    void play(Card card);
    void discard(Card card);
    void toggleHuman(int playerNumber);
    void startNextRound();
    void exit(); //might not ever need
    void endGame();
    void startGame(int seed);
    static const int NUM_PLAYERS = 4;
    static const int MAX_SCORE = 80;
private:
    Game* game_;

};


#endif //STRAIGHTS_GAMECONTROLLER_H
