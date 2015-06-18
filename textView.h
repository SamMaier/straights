//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_TEXTVIEW_H
#define STRAIGHTS_TEXTVIEW_H


#include "View.h"

class TextView : public View{
public:
    void alertPlayedCard(Player* player, Card card);
    void alertDiscardCard(Player* player, Card card);
    void alertRagequit(Player* player);
    void alertGameEnd(Game* game);
    void alertBeginRound(Player* firstPlayer);
    void alertEmptyHand(Player* player);
};


#endif //STRAIGHTS_TEXTVIEW_H
