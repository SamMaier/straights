#ifndef _PLAYER_
#define _PLAYER_

#include "hand.h"
#include "table.h"
#include "Command.h"

class Player {
public:
    Player(int playerNumber);
    virtual Command getPlay(const Table&) = 0;
    int getScore();
    void setHand(const Hand*);

protected:
    const Hand* hand_;

private:
    int playerNumber_;
    int score_;
};

#endif
