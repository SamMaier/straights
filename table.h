//
// Created by Shiranka Miskin on 6/13/15.
//

#ifndef STRAIGHTS_TABLE_H
#define STRAIGHTS_TABLE_H

#include <set>
#include "Card.h"

class Table {
public:
    Table();
    ~Table();
    void addCard(Card& card);
    std::set<Card> getCards() const;
    std::set<Card> getSuit(int suit) const;
private:
    std::set<Card>* m_cards;
};


std::ostream &operator<<(std::ostream &out, const Table &t);





#endif //STRAIGHTS_TABLE_H
