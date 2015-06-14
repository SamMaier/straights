//
// Created by Shiranka Miskin on 6/13/15.
//

#ifndef STRAIGHTS_DECK_H
#define STRAIGHTS_DECK_H


#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle(int seed = 0);

    const Card * getCards()const;
private:

    Card cards_[SUIT_COUNT * RANK_COUNT];
};

std::ostream &operator<<(std::ostream &out, const Deck &t);

#endif //STRAIGHTS_DECK_H
