//
// Created by Shiranka Miskin on 6/13/15.
//

#include "Deck.h"
#include <random>

Deck::Deck() {
    for (int suit = 0; suit < SUIT_COUNT; suit++) {
        for (int rank = 0; rank < RANK_COUNT; rank++) {
            cards_.push_back(Card((Suit) suit, (Rank) rank));
        }
    }
}

void Deck::shuffle(int seed){
    static std::mt19937 rng(seed);

    int n = NUM_CARDS;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

 const std::vector<Card>* Deck::getCards()const {
    return &cards_;
}

std::ostream &operator<<(std::ostream &out, const Deck &d) {
    int numCards = Deck::NUM_CARDS;
    const std::vector<Card>* cards = d.getCards();

    for (int suit = 0; suit < numCards / 13; suit++) {
        for (int rank = 0; rank < 13; rank++) {
            // If the card isn't the last card, add a trailing space before the next card
            out << cards->at(suit*13 + rank) << (rank != 12 ? " " : "");
        }

        // If the suit is not the very last suit, go to the next line to print the next suit
        if (suit != numCards / 13 - 1)
            out << std::endl;
    }

    return out;
}

