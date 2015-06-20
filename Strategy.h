#ifndef _STRATEGY_
#define _STRATEGY_

#include "Table.h"
#include "Hand.h"
#include "Command.h"

class Strategy {
public:
    virtual Command getPlay(const Hand&, const Table&) const = 0;
    virtual void alertPlay(const Hand&, const Table&) const {} // The strategy may want to complete an action only the first time a play is requested
    virtual ~Strategy(){};
};

#endif
