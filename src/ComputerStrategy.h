#ifndef _COMPUTER_STRATEGY_
#define _COMPUTER_STRATEGY_

#include "Strategy.h"

class ComputerStrategy : public Strategy {
public:
    Command getPlay(const Hand&, const Table&) const;
private:
};

#endif
