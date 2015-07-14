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
#include "View.h"
#include "Subject.h"

class View;
class Player;

enum Action {
    PLAY,
    DISCARD,
    RAGEQUIT
};

struct GameAction {
    Action action_;
    Card card_;
};

class Game : public Subject{
friend class GameController;
public:
    Game(int seed = 0, View* view = NULL);
    void run();
    const Deck* getDeck() const;
    const Table* getTable() const;
    static const int NUM_PLAYERS = 4;
    static const int MAX_SCORE = 80;
    static bool isValidPlay(const Card& card, const Hand& hand, const Table& table);
private:
    void play(Card card);
    void discard(Card card);
    void disablePlayer();
    void exit();
    void nextTurn();
    void nextRound();
    int currentPlayer_;
    Deck deck_;
    Table table_;
    std::vector<Hand> hands_;
    std::vector<std::vector<Card>> discards_;
    std::vector<Player> players_;
    bool running_;
    View* view_;
    int seed_; // A seed for the sorting algoirthm's randomization
    std::vector<GameAction> actions_;

};


#endif //STRAIGHTS_GAME_H
