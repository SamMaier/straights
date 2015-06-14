//
// Created by Shiranka Miskin on 6/14/15.
//

#include "hand.h"

std::ostream &operator<<(std::ostream &out, const Hand &h) {
    std::vector<Card> cards = *h.getCards();
    if (cards.size() < 0) return out;
    out << cards[0];
    for (int i = 1; i < cards.size(); i++)
        out << " " << cards[i];
    return out;
}
