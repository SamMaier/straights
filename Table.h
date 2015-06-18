//
// Created by Shiranka Miskin on 6/13/15.
//

#ifndef STRAIGHTS_TABLE_H
#define STRAIGHTS_TABLE_H

#include <set>
#include "Card.h"

class Table {
public:
    std::set<Card> getCardsOnBoard() const;
    void playCard(Card card);
    void clear() { cards_.clear(); }
    std::set<Card> getCards() const;
    std::set<Card> getSuit(int suit) const;
private:
    std::set<Card> cards_;
};


std::ostream &operator<<(std::ostream &out, const Table &t);





#endif //STRAIGHTS_TABLE_H
