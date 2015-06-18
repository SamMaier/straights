#ifndef _PLAYER_
#define _PLAYER_

#include "Hand.h"
#include "Table.h"
#include "Command.h"
#include "View.h"
#include "Strategy.h"

class View;

class Player {
public:
    Player(int playerNumber, bool isHuman, View*);
    Command getPlay(const Table&);
    std::string getName();
    void addScore(int score);
    int getScore();
    void setHand(const Hand* hand);
    void setDiscards(const std::vector<Card>* discards);
    const std::vector<Card>* getDiscards();
    const Hand* getHand();

private:
    int playerNumber_;
    bool isHuman_;
    int score_;
    const Hand* hand_;
    const std::vector<Card>* discards_;
    View* view_;
    Strategy* strategy_;
};

#endif
