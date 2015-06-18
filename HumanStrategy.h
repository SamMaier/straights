#ifndef _HUMAN_STRATEGY_
#define _HUMAN_STRATEGY_

#include "View.h"
#include "Strategy.h"

class HumanStrategy : public Strategy {
public:
    HumanStrategy(View*);
    Command getPlay(const Hand&, const Table&) const;
private:
    View* view_;
};

#endif
