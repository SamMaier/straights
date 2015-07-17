#ifndef _HUMAN_STRATEGY_
#define _HUMAN_STRATEGY_

#include "Strategy.h"

class HumanStrategy : public Strategy {
public:
    HumanStrategy();
    Command getPlay(const Hand&, const Table&) const;
};

#endif
