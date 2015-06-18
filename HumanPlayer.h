#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include "Player.h"
#include "hand.h"
#include "table.h"
#include "Command.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(int playerNumber);
    Command getPlay(const Table&);

private:
};

#endif
