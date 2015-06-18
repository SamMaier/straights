#ifndef _PLAYER_
#define _PLAYER_

#include "Hand.h"
#include "Table.h"
#include "Command.h"

class Player {
public:
    Player(int playerNumber);
    virtual Command getPlay(const Table&) = 0;
    std::string getName();
    void addScore(int score);
    int getScore();
    void setHand(const Hand* hand);
    void setDiscards(const std::vector<Card>* discards);
    const std::vector<Card>* getDiscards();
    const Hand* getHand();

protected:
    const Hand* hand_;
    const std::vector<Card>* discards_;

private:
    int playerNumber_;
    int score_;
};

#endif
