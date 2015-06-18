#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "hand.h"
#include "Command.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer(int playerNumber);
    Command& getPlay(const Table&) const;

private:
}

#endif
