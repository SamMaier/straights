#ifndef _HUMAN_STRATEGY_
#define _HUMAN_STRATEGY_

#include "View.h"
#include "Strategy.h"

class HumanStrategy : public Strategy {
public:
    HumanStrategy(View*);
    void alertPlay(const Hand&, const Table&) const;
    Command getPlay(const Hand&, const Table&) const;
private:
    View* view_;
    static bool isValidCommand(const Command&, const Hand& hand, const Table& table);
};

#endif
