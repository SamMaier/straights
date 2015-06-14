//
// Created by Shiranka Miskin on 6/14/15.
//

#ifndef STRAIGHTS_HAND_H
#define STRAIGHTS_HAND_H


#include <vector>
#include "Card.h"

class Hand {
public:
    Hand() : cards(new std::vector<Card>) {}
    void addCard(Card& card) {
        cards->push_back(card);
    }
    void removeCard(Card& card){
        std::remove(cards->begin(), cards->end(), card);
    }
    std::vector<Card>* getCards()const {
        return cards;
    }

private:
    std::vector<Card>* cards;
};


std::ostream &operator<<(std::ostream &out, const Hand &h);


#endif //STRAIGHTS_HAND_H
