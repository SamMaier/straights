#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "Hand.h"
#include "Table.h"
#include "Command.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer(int playerNumber);
    Command getPlay(const Table&);

private:
};

#endif
