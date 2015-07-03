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

    const std::vector<Card>* getCards() const;
    static const int NUM_CARDS = Suit::SUIT_COUNT * Rank::RANK_COUNT;
private:
    std::vector<Card> cards_;
};

std::ostream &operator<<(std::ostream &out, const Deck &d);

#endif //STRAIGHTS_DECK_H
