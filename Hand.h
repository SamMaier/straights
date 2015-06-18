//
// Created by Shiranka Miskin on 6/14/15.
//

#ifndef STRAIGHTS_HAND_H
#define STRAIGHTS_HAND_H


#include <vector>
#include <set>
#include <algorithm>
#include "Card.h"

class Hand {
public:
    void addCard(Card card) {
        cards_.push_back(card);
    }
    void removeCard(Card card){
        cards_.erase(std::remove(cards_.begin(), cards_.end(), card));
    }
    std::vector<Card> getCards() const {
        return cards_;
    }
    bool isEmpty() const{
        return cards_.size() <= 0;
    }

    std::vector<Card> getValidMoves(std::set<Card> cardsOnBoard) const;

private:
    std::vector<Card> cards_;
};


std::ostream &operator<<(std::ostream &out, const Hand &h);


#endif //STRAIGHTS_HAND_H
