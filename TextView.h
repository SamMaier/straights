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
    void alertGameEnd(Player* winner);
    void alertBeginRound(Player* firstPlayer);
    void alertEmptyHand(Player* player, int oldScore);
    void alertDeck(Deck *deck);
    void alertTable(Table* table);
    bool checkIfHuman(std::string playerName);
    void alertHand(Hand* hand);
    void alertLegalPlays(std::vector<Card> legalPlays);
    void alertIllegalPlay();
    void alertNoDiscard();
    Command getPlay();
};


#endif //STRAIGHTS_TEXTVIEW_H
