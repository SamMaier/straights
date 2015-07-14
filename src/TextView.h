//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_TEXTVIEW_H
#define STRAIGHTS_TEXTVIEW_H


#include "View.h"
#include "Observer.h"
#include "GameController.h"

class TextView : public View, public Observer{
public:
    void alertPlayedCard(const Player* player, Card card);
    void alertDiscardCard(const Player* player, Card card);
    void alertRagequit(const Player* player);
    void alertGameEnd(const Player* winner);
    void alertBeginRound(const Player* firstPlayer);
    void alertEmptyHand(const Player* player, int oldScore);
    void alertDeck(const Deck* deck);
    void alertTable(const Table* table);
    void alertHand(const Hand* hand);
    bool checkIfHuman(std::string playerName);
    void alertLegalPlays(std::vector<Card> legalPlays);
    void alertIllegalPlay();
    void alertNoDiscard();
    Command getPlay();
};


#endif //STRAIGHTS_TEXTVIEW_H
