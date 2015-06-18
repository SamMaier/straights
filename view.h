//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H


#include "Player.h"
#include "Card.h"

class Game;

class View {
public:
    virtual void alertPlayedCard(Player* player, Card card) {}
    virtual void alertDiscardCard(Player* player, Card card) {}
    virtual void alertRagequit(Player* player) {}
    virtual void alertGameEnd(Game* game) {}
};


#endif //STRAIGHTS_VIEW_H
