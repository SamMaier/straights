//
// Created by Shiranka Miskin on 6/17/15.
//

#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H


#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include "Command.h"

class Game;
class Player;

class View {
public:
    virtual void alertPlayedCard(const Player* player, Card card);
    virtual void alertDiscardCard(const Player* player, Card card);
    virtual void alertRagequit(const Player* player);
    virtual void alertGameEnd(const Player* winner);
    virtual void alertBeginRound(const Player* firstPlayer);
    virtual void alertEmptyHand(const Player* player, int oldScore);
    virtual void alertDeck(const Deck* deck);
    virtual void alertTable(const Table* table);
    virtual void alertHand(const Hand* hand);
    virtual void alertLegalPlays(std::vector<Card> legalPlays);
    virtual void alertIllegalPlay();
    virtual void alertNoDiscard();
    virtual Command getPlay() = 0;
    virtual bool checkIfHuman(std::string playerName) = 0;

};


#endif //STRAIGHTS_VIEW_H
