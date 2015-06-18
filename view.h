//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H


#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

class Game;

class View {
public:
    virtual void alertPlayedCard(Player* player, Card card);
    virtual void alertDiscardCard(Player* player, Card card);
    virtual void alertRagequit(Player* player);
    virtual void alertGameEnd(Player* winner);
    virtual void alertBeginRound(Player* firstPlayer);
    virtual void alertEmptyHand(Player* player, int oldScore);
    virtual void alertDeck(Deck* deck);
    virtual void alertTable(Table* table);
    virtual void alertHand(Hand* hand);
    virtual void alertLegalPlays(std::vector<Card> legalPlays);
    virtual void alertIllegalPlay();
    virtual void alertNoDiscard();
    virtual Command getPlay();
    virtual bool checkIfHuman(std::string playerName);

};


#endif //STRAIGHTS_VIEW_H
