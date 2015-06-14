//
// Created by Shiranka Miskin on 6/13/15.
//

#include "deck.h"
#include <random>

Deck::Deck() {
    for (int suit = 0; suit < SUIT_COUNT; suit++) {
        for (int rank = 0; rank < RANK_COUNT; rank++) {
            cards_[suit*RANK_COUNT + rank] = Card((Suit) suit, (Rank) rank);
        }
    }
}


void Deck::shuffle(int seed){
    static std::mt19937 rng(seed);

    int n = SUIT_COUNT * RANK_COUNT;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

const Card* Deck::getCards()const {
    return cards_;
}

std::ostream &operator<<(std::ostream &out, const Deck &d) {
    int numCards = SUIT_COUNT * RANK_COUNT;
    const Card* cards = d.getCards();
    for (int i = 0; i < numCards / 13; i++) {
        for (int j = 0; j < 13; j++) {
            out << cards[i*13 + j] << (j != 12 ? " " : "");
        }
        if (i != numCards / 13 - 1)
            out << std::endl;
    }

    return out;
}

