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
    ~Player();
    Command getPlay(const Table&) const;
    std::string getName() const;
    void addScore(int score);
    int getScore() const;
    void setHand(const Hand* hand);
    void setDiscards(const std::vector<Card>* discards);
    const std::vector<Card>* getDiscards() const;
    const Hand* getHand() const;

private:
    int playerNumber_;
    int score_;
    const Hand* hand_;
    const std::vector<Card>* discards_;
    View* view_;
    Strategy* strategy_;
};

#endif
