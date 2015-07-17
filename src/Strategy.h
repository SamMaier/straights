#ifndef _STRATEGY_
#define _STRATEGY_

#include "Table.h"
#include "Hand.h"
#include "Command.h"

class Strategy {
public:
    virtual Command getPlay(const Hand&, const Table&) const = 0;
    virtual ~Strategy(){};
};

#endif
